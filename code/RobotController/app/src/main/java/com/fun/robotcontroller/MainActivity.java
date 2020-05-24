package com.fun.robotcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.UserHandle;
import android.widget.Button;
import android.widget.TextView;

import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private int state = 0;
    private Robot robot = Robot.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        state = robot.getState();

        setRobotState();

        Button mainSelectButton = findViewById(R.id.mainSwitchButton);
        mainSelectButton.setOnClickListener(v -> {
            state = robot.switchState();
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

    private void setRobotState() {
        TextView robotState = findViewById(R.id.RobotState);

        switch (state) {
            case 0:
                robotState.setText("当前机器人状态：待机");
                break;
            case 1:
                robotState.setText("当前机器人状态：工作中");
                break;
            case -1:
                robotState.setText("获取机器人状态失败");
                break;
        }
    }
}
