package com.fun.robotcontroller;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class MapActivity extends AppCompatActivity {
    NavMap map = NavMap.getInstance();
    Robot robot = Robot.getInstance();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map);
        robot.getMap();

        TextView mapTitle = findViewById(R.id.mapTitle);

        if (map.getState() == -1) {
            mapTitle.setText("未能获取地图信息");
        } else {
            mapTitle.setText("地图");
        }

        ImageView mapView = findViewById(R.id.mapView);

        Button refreshButton = findViewById(R.id.refreshButton);
        refreshButton.setOnClickListener(v -> {
            robot.getMap();
            if (map.getState() == -1) {
                mapTitle.setText("未能获取地图信息");
                mapView.setVisibility(View.INVISIBLE);
            } else {
                mapTitle.setText("地图");
                mapView.setVisibility(View.VISIBLE);
                mapView.setImageBitmap(map.getMap());
            }
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
}
