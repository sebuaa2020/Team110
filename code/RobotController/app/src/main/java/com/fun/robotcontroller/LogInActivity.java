package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

public class LogInActivity extends AppCompatActivity {
    private Robot robot = Robot.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        EditText user = findViewById(R.id.user);
        EditText pwd = findViewById(R.id.pwd);

        Button logInButton = findViewById(R.id.log_in);
        logInButton.setOnClickListener(v -> {
            int logInState = robot.logIn(user.toString(), pwd.toString());

            if (logInState == 1) {
                user.setText("");
                pwd.setText("");
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivity(intent);
            } else if (logInState == 0) {
                pwd.setText("");
                startDialog("密码错误");
            } else if (logInState == -1) {
                user.setText("");
                pwd.setText("");
                startDialog("用户不存在");
            } else {
                startDialog("请求失败");
            }
        });

        Button signUpButton = findViewById(R.id.sign_up);
        signUpButton.setOnClickListener(v -> {
            int signUpState = robot.signUp(user.toString(), pwd.toString());

            if (signUpState == 1) {
                user.setText("");
                pwd.setText("");
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                startActivity(intent);
            } else if (signUpState == -1) {
                user.setText("");
                pwd.setText("");
                startDialog("用户已存在");
            } else {
                startDialog("请求失败");
            }
        });
    }

    private void startDialog(String msg) {
        AlertDialog.Builder builder = new AlertDialog.Builder(LogInActivity.this);
        //    设置Title的图标
        builder.setIcon(R.drawable.icon);
        //    设置Title的内容
        builder.setTitle("Error");
        //    设置Content来显示一个信息
        builder.setMessage(msg);
        //    设置一个PositiveButton
        builder.setPositiveButton("确定", (dialog, which) -> {
        });

        builder.show();
    }
}
