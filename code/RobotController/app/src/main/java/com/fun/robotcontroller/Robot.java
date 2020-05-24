// 获取机器人的状态信息，并发布指令至机器人

package com.fun.robotcontroller;

import Utils.AsynNetUtils;

public class Robot {
    final private static Robot instance = new Robot();
    private int state = 0;

    private Robot() {
    }

    static Robot getInstance() {
        return instance;
    }

    int getState() {
        try {
            sendHttp("get_state");
        } catch (Exception e) {
            state = -1;
        }
        return state;
    }

    int switchState() {
        try {
            sendHttp("switch_state");
            sendHttp("get_state");
        } catch (Exception e) {

        }
        return state;
    }

    private void sendHttp(String cmd) {
        AsynNetUtils.post("http://10.136.107.127:5000", cmd, response -> {
            try {
                state = Integer.parseInt(response);
            } catch (Exception e) {
                //抛出网络请求异常
                e.printStackTrace();
            }
        });
    }
}
