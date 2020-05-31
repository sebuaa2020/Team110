package com.fun.robotcontroller;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;

import java.util.ArrayList;

import Utils.ViewPoint;

import static java.lang.Math.atan2;
import static java.lang.Math.cos;
import static java.lang.Math.pow;
import static java.lang.Math.sin;
import static java.lang.Math.sqrt;

public class MapImageView extends androidx.appcompat.widget.AppCompatImageView {
    private Paint paint = new Paint();
    private ArrayList<ViewPoint> current = new ArrayList<>();
    private NavMap map = NavMap.getInstance();
    private float height = getHeight();
    private float width = getWidth();
    private float pose_x, pose_y, pose_theta;
    private float scaleX = (float) 19.71;
    private float scaleY = (float) 22.94;

    public MapImageView(Context context) {
        super(context);
    }

    public MapImageView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public MapImageView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float clickX = event.getX();
        float clickY = event.getY();

        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            return true;
        } else if (event.getAction() == MotionEvent.ACTION_MOVE) {
            ViewPoint point = new ViewPoint();
            point.x = clickX;
            point.y = clickY;
            //在移动时添加所经过的点
            current.add(point);

            invalidate();
            return true;
        } else if (event.getAction() == MotionEvent.ACTION_UP) {
            //添加画过的线
            current = new ArrayList<>();
        }
        return super.onTouchEvent(event);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        paint = new Paint();
        paint.setStrokeWidth(8);
        paint.setColor(Color.BLUE);

        height = getHeight();
        width = getWidth();

        float curX = (float) map.getX() * scaleX + width / 2;
        float curY = height / 2 - (float) map.getY() * scaleY;

        canvas.drawCircle(curX, curY, 10, paint);

        canvas.drawLine(curX, curY, curX + 20 * (float) cos(map.getTheta()),
                curY - 20 * (float) sin(map.getTheta()), paint);
        paint.setColor(Color.RED);

        if (current.size() > 2) {
            float startX = current.get(0).x;
            float startY = current.get(0).y;
            canvas.drawCircle(startX, startY, 10, paint);

            pose_x = (startX - width / 2) / scaleX + (float) 0.7302;
            pose_y = (height / 2 - startY) / scaleY - (float) 0.3423;

            float endX = current.get(current.size() - 1).x;
            float endY = current.get(current.size() - 1).y;

            pose_theta = (float) atan2(startY - endY, endX - startX);

            float length = (float) sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));

            if (length != 0) {
                endX = startX + (endX - startX) / length * 20;
                endY = startY + (endY - startY) / length * 20;

                canvas.drawLine(startX, startY, endX, endY, paint);
            }
        }
    }

    public float getPose_x() {
        return pose_x;
    }

    public float getPose_y() {
        return pose_y;
    }

    public float getPose_theta() {
        return pose_theta;
    }
}
