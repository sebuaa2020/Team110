import base64
import os
from io import BytesIO
from PIL import Image
import subprocess


class Robot:
    def __init__(self):
        self.state = 0
        self.pose = {"x": 0.0, "y": 0.0, "theta": 0.0}
        self.nav_point = {"x": 0.0, "y": 0.0, "theta": 0.0}
        self.simulator = None
        self.grab_part = None
        self.pass_part = None

    def get_state(self):
        return self.state

    def switch_state(self):
        if self.state == 0:
            self.activate()
        else:
            self.deactivate()
        return self.state

    def get_map(self):
        map = Image.open("../map.pgm")
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
                output = cur_pos.stdout.readline()
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
            subprocess.Popen("pkill home_core", shell=True)
        print(self.pose)
        return base64_str.decode()

    def navigation(self, x, y, theta):
        if self.state == 1:
            self.nav_point['x'] = x
            self.nav_point['y'] = y
            self.nav_point['theta'] = theta
        print(x, y, theta)

    def activate(self):
        self.simulator = subprocess.Popen("roslaunch wpr_simulation wpb_simple.launch", stdout=subprocess.PIPE,
                                          shell=True, preexec_fn=os.setsid)
        self.grab_part = subprocess.Popen("roslaunch robot_grab grab_action.launch", stdout=subprocess.PIPE,
                                          shell=True, preexec_fn=os.setsid)
        self.pass_part = subprocess.Popen("roslaunch robot_grab pass_action.launch", stdout=subprocess.PIPE,
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
        self.state = 0
