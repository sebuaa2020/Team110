package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import Utils.AsynNetUtils;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class MapActivity extends AppCompatActivity {
    NavMap map = NavMap.getInstance();


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map);
        getMap();
        TextView mapTitle = findViewById(R.id.mapTitle);

        if (map.getState() == -1) {
            mapTitle.setText("未能获取地图信息");
        } else {
            mapTitle.setText("地图");
        }

        Button refreshButton = findViewById(R.id.refreshButton);
        refreshButton.setOnClickListener(v -> {
            getMap();
        });

        Button eventButton = findViewById(R.id.homeButton);
        eventButton.setOnClickListener(v -> {
            Intent intent = new Intent(getApplicationContext(), MainActivity.class);
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

    private void getMap() {
        JSONObject cmd = new JSONObject();
        try {
            cmd.put("cmd", "get_map");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {
            String jsonString = cmd.toString();
            AsynNetUtils.post(jsonString, response -> {
                JSONObject res = new JSONObject();
                try {
                    res = new JSONObject(response);
                    setMap(res);
                    refresh();
                } catch (Exception e) {
                    map.setState(-1);
                    e.printStackTrace();
                }
            });
        } catch (Exception e) {
            map.setState(-1);
            e.printStackTrace();
        }
    }

    private void setMap(JSONObject response) {
        try {
            int result = response.getInt("result");
            map.setState(result);
            if (result > 0) {
                map.setMap(response.getString("map"));
//                map.setX(response.getDouble("pose_x"));
//                map.setY(response.getDouble("pose_y"));
//                map.setTheta(response.getDouble("pose_theta"));
            }
        } catch (JSONException e) {
            map.setState(-1);
            e.printStackTrace();
        }
    }

    private void refresh() {
        TextView mapTitle = findViewById(R.id.mapTitle);
        ImageView mapView = findViewById(R.id.mapView);
        if (map.getState() == -1) {
            mapTitle.setText("未能获取地图信息");
            mapView.setVisibility(View.INVISIBLE);
        } else {
            mapTitle.setText("地图");
            mapView.setVisibility(View.VISIBLE);
            mapView.setImageBitmap(map.getMap());
        }
    }
}
