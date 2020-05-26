package com.fun.robotcontroller;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;

public class NavMap {
    final private static NavMap instance = new NavMap();
    Bitmap map;
    private int state = -1;
    private double x;
    private double y;
    private double theta;

    private NavMap() {
    }

    static NavMap getInstance() {
        return instance;
    }

    void setMap(String rawMap) {
        byte[] bytes = Base64.decode(rawMap, Base64.DEFAULT);
        map = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
    }

    void setState(int state) {
        this.state = state;
    }

    int getState() {
        return state;
    }

    Bitmap getMap() {
        return map;
    }

    public double getTheta() {
        return theta;
    }

    void setTheta(double theta) {
        this.theta = theta;
    }

    public double getY() {
        return y;
    }

    void setY(double y) {
        this.y = y;
    }

    public double getX() {
        return x;
    }

    void setX(double x) {
        this.x = x;
    }
}
