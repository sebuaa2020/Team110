// 获取机器人的状态信息，并发布指令至机器人

package com.fun.robotcontroller;

import org.json.JSONException;
import org.json.JSONObject;

import Utils.AsynNetUtils;
import androidx.appcompat.app.AlertDialog;

public class Robot {
    final private static Robot instance = new Robot();
    private int state = 0;
    private String user = "root";
    private JSONObject response;

    private Robot() {
    }

    static Robot getInstance() {
        return instance;
    }

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
        }
        return state;
    }

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
            e.printStackTrace();
        }
        return state;
    }

    boolean logIn(String user, String pwd) {
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
        }
        return true;
    }

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
            e.printStackTrace();
        }
    }

    void navigationPoint() {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "navigation");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            sendHttp(cmd);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

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
