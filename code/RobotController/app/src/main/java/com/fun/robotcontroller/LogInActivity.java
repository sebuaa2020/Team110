package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class LogInActivity extends AppCompatActivity {
    private Robot robot = Robot.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Button logInButton = findViewById(R.id.log_in);
        logInButton.setOnClickListener(v -> {
            EditText user = findViewById(R.id.user);
            EditText pwd = findViewById(R.id.pwd);

            boolean logInState = robot.logIn(user.toString(), pwd.toString());

            if (logInState) {
                user.setText("");
                pwd.setText("");
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivity(intent);
            } else {
                pwd.setText("");
            }
        });

    }
}
