package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class UserActivity extends AppCompatActivity {
    private Robot robot = Robot.getInstance();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user);

        Button adviseButton = findViewById(R.id.advise);
        adviseButton.setOnClickListener(v -> {
            EditText advice = findViewById(R.id.advice);
            robot.userAdvise(advice.getText().toString());
            advice.setText("");
        });

        Button eventButton = findViewById(R.id.homeButton);
        eventButton.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), MainActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            startActivity(intent);
        });

        Button rewardButton = findViewById(R.id.historyButton);
        rewardButton.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), MapActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            startActivity(intent);
        });
    }
}
