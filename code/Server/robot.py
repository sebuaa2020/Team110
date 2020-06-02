import base64
import os
from io import BytesIO
from PIL import Image
import subprocess
from xml.dom.minidom import parse
import math
import time


def trans(pitch, roll, yaw):
    cy = math.cos(yaw * 0.5)
    sy = math.sin(yaw * 0.5)
    cp = math.cos(pitch * 0.5)
    sp = math.sin(pitch * 0.5)
    cr = math.cos(roll * 0.5)
    sr = math.sin(roll * 0.5)
    return sy * cp * cr - cy * sp * sr, cy * cp * cr + sy * sp * sr


def navi_part(x, y, theta):
    z, w = trans(0, 0, theta)
    domTree = parse("../catkin_ws/src/my_nav/waypoints.xml")
    pos_x = domTree.getElementsByTagName("Pos_x")[0]
    pos_x.childNodes[0].data = x
    pos_y = domTree.getElementsByTagName("Pos_y")[0]
    pos_y.childNodes[0].data = y
    ori_z = domTree.getElementsByTagName("Ori_z")[0]
    ori_z.childNodes[0].data = z
    ori_w = domTree.getElementsByTagName("Ori_w")[0]
    ori_w.childNodes[0].data = w
    with open('../catkin_ws/src/my_nav/waypoints.xml', 'w') as f:
        # 缩进 - 换行 - 编码
        domTree.writexml(f, addindent='', encoding='utf-8')
    subprocess.Popen("rosrun waterplus_map_tools wp_manager _load:=/home/eric/catkin_ws/src/my_nav/waypoints.xml", shell=True)


class Robot:
    def __init__(self):
        self.state = 0
        self.pose = {"x": 0.0, "y": 0.0, "theta": 0.0}
        self.nav_point = {"x": 0.0, "y": 0.0, "theta": 0.0}
        self.simulator = None
        self.grab_part = None
        self.pass_part = None
        self.voice_part = None
        self.nav_part = None

    def get_state(self):
        return self.state

    def switch_state(self):
        if self.state == 0:
            self.activate()
        else:
            self.deactivate()
        return self.state

    def get_map(self):
        map = Image.open("../catkin_ws/src/my_nav/maps/map.pgm")
        output_buffer = BytesIO()
        map.save(output_buffer, format='JPEG')
        byte_data = output_buffer.getvalue()
        base64_str = base64.b64encode(byte_data)
        if self.state == 0:
            self.pose['x'] = 0.0
            self.pose['y'] = 0.0
            self.pose['theta'] = 0.0
        else:
            cur_pos = subprocess.Popen("rosrun robot_grab home_core", stdout=subprocess.PIPE, shell=True)
            x = 0
            while True:
                output = str(cur_pos.stdout.readline())
                x = x + 1
                if x > 3:
                    break
                if output.find("pose_x") >= 0:
                    index_x = output.find('pose_x') + 7
                    index_y = output.find('pose_y') + 7
                    index_theta = output.find('pose_theta') + 11
                    try:
                        self.pose['x'] = float(output[index_x: index_x + 6])
                        self.pose['y'] = float(output[index_y: index_y + 6])
                        self.pose['theta'] = float(output[index_theta: index_theta + 6])
                        break
                    except:
                        self.pose['x'] = 0.0
                        self.pose['y'] = 0.0
                        self.pose['theta'] = 0.0
            cur_pos.kill()
        print(self.pose)
        return base64_str.decode()

    def navigation(self, x, y, theta):
        if self.state == 1:
            self.nav_point['x'] = x
            self.nav_point['y'] = y
            self.nav_point['theta'] = theta
            navi_part(x, y, theta)
        print(x, y, theta)

    def activate(self):
        self.simulator = subprocess.Popen("roslaunch wpr_simulation wpb_simple.launch", stdout=subprocess.PIPE,
                                          shell=True, preexec_fn=os.setsid)
        time.sleep(3)
        self.grab_part = subprocess.Popen("roslaunch robot_grab grab_action.launch", stdout=subprocess.PIPE,
                                         shell=True, preexec_fn=os.setsid)
        self.pass_part = subprocess.Popen("roslaunch robot_grab pass_action.launch", stdout=subprocess.PIPE,
                                          shell=True, preexec_fn=os.setsid)
        self.voice_part = subprocess.Popen("roslaunch xfei_asr xfei_main.launch ", stdout=subprocess.PIPE,
                                           shell=True, preexec_fn=os.setsid)
        self.nav_part = subprocess.Popen("roslaunch my_nav my_navigation.launch", stdout=subprocess.PIPE,
                                         shell=True, preexec_fn=os.setsid)
        self.state = 1

    def deactivate(self):
        if self.simulator is not None:
            os.killpg(os.getpgid(self.simulator.pid), 9)
            subprocess.Popen("pkill gzserver", shell=True)
            subprocess.Popen("pkill gzclient", shell=True)
            print("simulator end")
            self.simulator = None
        if self.grab_part is not None:
            os.killpg(os.getpgid(self.grab_part.pid), 9)
            subprocess.Popen("pkill rviz", shell=True)
            subprocess.Popen("pkill grab_server", shell=True)
            subprocess.Popen("pkill home_core", shell=True)
            subprocess.Popen("pkill state_publisher", shell=True)
            subprocess.Popen("pkill python2 -9", shell=True)
            print("grab_part end")
            self.grab_part = None
        if self.pass_part is not None:
            os.killpg(os.getpgid(self.pass_part.pid), 9)
            subprocess.Popen("pkill pass_server", shell=True)
            self.pass_part = None
        if self.voice_part is not None:
            os.killpg(os.getpgid(self.voice_part.pid), 9)
            subprocess.Popen("killall -9 iat_publish_speak", shell=True)
            subprocess.Popen("killall -9 tts_subscribe_speak", shell=True)
            subprocess.Popen("pkill main_control", shell=True)
        if self.nav_part is not None:
            os.killpg(os.getpgid(self.nav_part.pid), 9)
            subprocess.Popen("killall wp_manager", shell=True)
            subprocess.Popen("killall amcl", shell=True)
            subprocess.Popen("killall move_base", shell=True)
            subprocess.Popen("killall map_server", shell=True)
            subprocess.Popen("pkill state_publisher", shell=True)
            subprocess.Popen("pkill python2 -9", shell=True)
        subprocess.Popen("pkill rosout", shell=True)
        self.state = 0
