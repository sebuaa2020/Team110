// 获取机器人的状态信息，并发布指令至机器人

package com.fun.robotcontroller;

import org.json.JSONException;
import org.json.JSONObject;

import Utils.AsynNetUtils;

public class Robot {
    final private static Robot instance = new Robot();
    private int state = 0;
    private String user = "root";
    private JSONObject response = new JSONObject();
    private NavMap map = NavMap.getInstance();

    private Robot() {
    }

    static Robot getInstance() {
        return instance;
    }

    /*获取机器人状态
    未能获得信息返回 -1
    获得休眠信息返回 0
    获得工作信息返回 1
     */
    int getState() {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "get_state");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            state = -1;
            e.printStackTrace();
            return state;
        }
        try {
            int result = response.getInt("result");
            if (result > 0) {
                state = response.getInt("state");
            } else {
                state = -1;
            }
        } catch (JSONException e) {
            state = -1;
            e.printStackTrace();
        }
        return state;
    }

    /*
        切换机器人状态
        未能获得信息返回 -1
        获得休眠信息返回 0
        获得工作信息返回 1
     */
    int switchState() {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "switch_state");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            state = -1;
            e.printStackTrace();
            return state;
        }
        try {
            int result = response.getInt("result");
            if (result > 0) {
                state = response.getInt("state");
            } else {
                state = -1;
            }
        } catch (JSONException e) {
            state = -1;
            e.printStackTrace();
        }
        return state;
    }

    /*
    用户登录
    成功返回1
    密码错误返回0
    用户不存在返回-1
    请求失败返回-2
    */
    int logIn(String user, String pwd) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "log_in");
            cmd.put("user", user);
            cmd.put("pwd", pwd);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            e.printStackTrace();
            return -2;
        }
        try {
            int result = response.getInt("result");
            if (result > 0) {
                return response.getInt("log_in_result");
            } else {
                return -2;
            }
        } catch (JSONException e) {
            e.printStackTrace();
            return -2;
        }
    }

    /*
        用户注册
        成功返回1
        用户已存在返回-1
        请求失败返回-2
    */
    int signUp(String user, String pwd) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "sign_up");
            cmd.put("user", user);
            cmd.put("pwd", pwd);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            e.printStackTrace();
            return -2;
        }
        try {
            int result = response.getInt("result");
            if (result > 0) {
                return response.getInt("sign_up_result");
            } else {
                return -2;
            }
        } catch (JSONException e) {
            e.printStackTrace();
            return -2;
        }
    }

    /*
    获取地图信息
    成功就把地图信息写至NavMap里
    失败就设置NavMap的state为-1
     */
    void getMap() {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "get_map");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            map.setState(-1);
            e.printStackTrace();
            return;
        }
        try {
            int result = response.getInt("result");
            map.setState(result);
            if (result > 0) {
                map.setMap(response.getString("map"));
                map.setX(response.getDouble("pose_x"));
                map.setY(response.getDouble("pose_y"));
                map.setTheta(response.getDouble("pose_theta"));
            }
        } catch (JSONException e) {
            map.setState(-1);
            e.printStackTrace();
        }
    }

    /*
    设置导航点信息
     */
    void navigationPoint(double x, double y, double theta) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "navigation");
            cmd.put("x", x);
            cmd.put("y", y);
            cmd.put("theta", theta);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /*
    提交反馈信息
     */
    void userAdvise(String advice) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "advise");
            cmd.put("user", user);
            cmd.put("advise_content", advice);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void sendHttp(JSONObject cmd) throws Exception {
        final String[] res = {""};
        AsynNetUtils.post("", cmd.toString(), response -> {
            res[0] = response;
        });
        this.response = new JSONObject(res[0]);
    }
}
