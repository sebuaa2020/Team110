package com.fun.robotcontroller;

import Utils.AsynNetUtils;
import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.UserHandle;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private int state = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getState("get_state");

        Button mainSelectButton = findViewById(R.id.mainSwitchButton);
        mainSelectButton.setOnClickListener(v -> {
            getState("switch_state");
        });

        Button eventButton = findViewById(R.id.historyButton);
        eventButton.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), MapActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            startActivity(intent);
        });
        Button rewardButton = findViewById(R.id.aboutButton);
        rewardButton.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), UserActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            startActivity(intent);
        });
    }

    void getState(String command) {
        TextView robotState = findViewById(R.id.RobotState);
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", command);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            String jsonString = cmd.toString();
            AsynNetUtils.post("http://192.168.0.103:5000", jsonString, response -> {
                JSONObject res = new JSONObject();
                try {
                    res = new JSONObject(response);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                try {
                    int result = res.getInt("result");
                    if (result > 0) {
                        if (res.getInt("state") > 0)
                            robotState.setText("当前机器人状态：工作中");
                        else
                            robotState.setText("当前机器人状态：待机");
                    } else {
                        robotState.setText("获取机器人状态失败");
                    }
                } catch (Exception e) {
                    robotState.setText("获取机器人状态失败");
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            robotState.setText("获取机器人状态失败");
            e.printStackTrace();
        }
    }
}
