package com.visualgui;

public class NativeBridge {
    static {
        System.loadLibrary("visualgui");
    }

    public native void onSurfaceCreated();
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();
    public native void onTouchEvent(int action, float x, float y, int pointerId);
}
