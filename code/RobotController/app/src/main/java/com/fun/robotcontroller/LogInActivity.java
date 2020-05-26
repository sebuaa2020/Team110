package com.fun.robotcontroller;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.JsonReader;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import Utils.AsynNetUtils;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

public class LogInActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        EditText user = findViewById(R.id.user);
        EditText pwd = findViewById(R.id.pwd);

        Button logInButton = findViewById(R.id.log_in);
        logInButton.setOnClickListener(v -> {
            logIn(user.getText().toString(), pwd.getText().toString());
        });

        Button signUpButton = findViewById(R.id.sign_up);
        signUpButton.setOnClickListener(v -> {
            signUp(user.getText().toString(), pwd.getText().toString());
        });
    }

    void logIn(String user, String pwd) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "log_in");
            cmd.put("user", user);
            cmd.put("pwd", pwd);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            String jsonString = cmd.toString();
            TextView userText = findViewById(R.id.user);
            TextView pwdText = findViewById(R.id.pwd);
            AsynNetUtils.post("http://192.168.0.103:5000", jsonString, response -> {
                JSONObject res = new JSONObject();
                try {
                    res = new JSONObject(response);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                int logInState = 0;
                try {
                    logInState = res.getInt("log_in_result");
                    if (logInState == 1) {
                        userText.setText("");
                        pwdText.setText("");
                        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        startActivity(intent);
                    } else if (logInState == 0) {
                        pwdText.setText("");
                        startDialog("密码错误");
                    } else if (logInState == -1) {
                        userText.setText("");
                        pwdText.setText("");
                        startDialog("用户不存在");
                    } else {
                        startDialog("请求失败");
                    }
                } catch (JSONException e) {
                    startDialog("请求失败");
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            startDialog("请求失败");
            e.printStackTrace();
        }
    }

    private void signUp(String user, String pwd) {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "sign_up");
            cmd.put("user", user);
            cmd.put("pwd", pwd);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            String jsonString = cmd.toString();
            TextView userText = findViewById(R.id.user);
            TextView pwdText = findViewById(R.id.pwd);
            AsynNetUtils.post("http://192.168.0.103:5000", jsonString, response -> {
                JSONObject res = new JSONObject();
                try {
                    res = new JSONObject(response);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                int signUpState = 0;
                try {
                    signUpState = res.getInt("sign_up_result");
                    if (signUpState == 1) {
                        userText.setText("");
                        pwdText.setText("");
                        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
                        startActivity(intent);
                    } else if (signUpState == -1) {
                        userText.setText("");
                        pwdText.setText("");
                        startDialog("用户已存在");
                    } else {
                        startDialog("请求失败");
                    }
                } catch (JSONException e) {
                    startDialog("请求失败");
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            startDialog("请求失败");
            e.printStackTrace();
        }
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
