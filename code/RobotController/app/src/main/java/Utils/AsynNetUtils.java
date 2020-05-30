package Utils;

import android.os.Handler;

import org.json.JSONException;

public class AsynNetUtils {
    public interface Callback {
        void onResponse(String response);
    }

    public static void get(final String url, final Callback callback) {
        final Handler handler = new Handler();
        new Thread(() -> {
            final String response = NetUtils.get(url);
            handler.post(() -> callback.onResponse(response));
        }).start();
    }

    public static void post(final String content, final Callback callback) {
        final Handler handler = new Handler();
        final String url = "http://192.168.0.101:5000";
        new Thread(() -> {
            final String response = NetUtils.post(url, content);
            handler.post(() -> callback.onResponse(response));
        }).start();
    }
}
