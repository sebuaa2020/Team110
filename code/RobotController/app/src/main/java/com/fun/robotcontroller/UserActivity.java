package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import org.json.JSONException;
import org.json.JSONObject;

import Utils.AsynNetUtils;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class UserActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user);

        Button adviseButton = findViewById(R.id.advise);
        adviseButton.setOnClickListener(v -> {
            EditText advice = findViewById(R.id.advice);
            JSONObject cmd = new JSONObject();
            try {
                cmd.put("cmd", "advise");
                cmd.put("advice", advice.getText().toString());
            } catch (JSONException e) {
                e.printStackTrace();
            }
            String jsonString = cmd.toString();
            try {
                AsynNetUtils.post(jsonString, response -> {
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
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
