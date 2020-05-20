package Utils;

import android.os.Handler;

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

    public static void post(final String url, final String content, final Callback callback) {
        final Handler handler = new Handler();
        new Thread(() -> {
            final String response = NetUtils.post(url, content);
            handler.post(() -> callback.onResponse(response));
        }).start();
    }
}
