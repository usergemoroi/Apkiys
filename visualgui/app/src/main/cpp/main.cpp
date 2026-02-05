#include <jni.h>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <memory>
#include <chrono>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"

#include "GUI.h"
#include "ESP.h"
#include "Aimbot.h"

#define LOG_TAG "VisualGUI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Global instances
std::unique_ptr<GUI> g_GUI;
std::unique_ptr<ESP> g_ESP;
std::unique_ptr<Aimbot> g_Aimbot;

// EGL context
static EGLDisplay g_EGLDisplay = EGL_NO_DISPLAY;
static EGLSurface g_EGLSurface = EGL_NO_SURFACE;
static EGLContext g_EGLContext = EGL_NO_CONTEXT;
static EGLConfig g_EGLConfig = nullptr;

// Screen dimensions
static int g_ScreenWidth = 0;
static int g_ScreenHeight = 0;

// Touch input state
static bool g_TouchPressed = false;
static float g_TouchX = 0.0f;
static float g_TouchY = 0.0f;

// Initialize EGL
static bool InitEGL() {
    LOGI("Initializing EGL");

    g_EGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_EGLDisplay == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay failed");
        return false;
    }

    EGLint major, minor;
    if (!eglInitialize(g_EGLDisplay, &major, &minor)) {
        LOGE("eglInitialize failed");
        return false;
    }

    LOGI("EGL version: %d.%d", major, minor);

    const EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    EGLint numConfigs;
    if (!eglChooseConfig(g_EGLDisplay, configAttribs, &g_EGLConfig, 1, &numConfigs)) {
        LOGE("eglChooseConfig failed");
        return false;
    }

    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };

    g_EGLContext = eglCreateContext(g_EGLDisplay, g_EGLConfig, EGL_NO_CONTEXT, contextAttribs);
    if (g_EGLContext == EGL_NO_CONTEXT) {
        LOGE("eglCreateContext failed");
        return false;
    }

    return true;
}

// Shutdown EGL
static void ShutdownEGL() {
    LOGI("Shutting down EGL");
    
    if (g_EGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(g_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        
        if (g_EGLContext != EGL_NO_CONTEXT) {
            eglDestroyContext(g_EGLDisplay, g_EGLContext);
            g_EGLContext = EGL_NO_CONTEXT;
        }
        
        if (g_EGLSurface != EGL_NO_SURFACE) {
            eglDestroySurface(g_EGLDisplay, g_EGLSurface);
            g_EGLSurface = EGL_NO_SURFACE;
        }
        
        eglTerminate(g_EGLDisplay);
        g_EGLDisplay = EGL_NO_DISPLAY;
    }
}

// Initialize ImGui and GUI
static bool InitImGui() {
    LOGI("Initializing ImGui");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup display size
    io.DisplaySize = ImVec2((float)g_ScreenWidth, (float)g_ScreenHeight);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    // Setup backend
    if (!ImGui_ImplOpenGL3_Init("#version 300 es")) {
        LOGE("ImGui_ImplOpenGL3_Init failed");
        return false;
    }

    // Create global instances
    g_GUI = std::make_unique<GUI>();
    g_ESP = std::make_unique<ESP>();
    g_Aimbot = std::make_unique<Aimbot>();

    // Initialize GUI
    if (!g_GUI->Init()) {
        LOGE("GUI initialization failed");
        return false;
    }

    // Set global pointers for GUI callbacks
    ::g_ESP = g_ESP.get();
    ::g_Aimbot = g_Aimbot.get();
    ::g_GUI = g_GUI.get();

    LOGI("ImGui and GUI initialized successfully");
    return true;
}

// Shutdown ImGui and GUI
static void ShutdownImGui() {
    LOGI("Shutting down ImGui");

    if (g_GUI) {
        g_GUI->Shutdown();
        g_GUI.reset();
    }

    g_ESP.reset();
    g_Aimbot.reset();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

// JNI Functions
extern "C" {

JNIEXPORT void JNICALL
Java_com_visualgui_NativeBridge_onSurfaceCreated(JNIEnv* env, jobject thiz) {
    LOGI("onSurfaceCreated");
    
    if (!InitEGL()) {
        LOGE("Failed to initialize EGL");
        return;
    }
}

JNIEXPORT void JNICALL
Java_com_visualgui_NativeBridge_onSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height) {
    LOGI("onSurfaceChanged: %dx%d", width, height);
    
    g_ScreenWidth = width;
    g_ScreenHeight = height;
    
    glViewport(0, 0, width, height);
    
    if (!g_GUI) {
        if (!InitImGui()) {
            LOGE("Failed to initialize ImGui");
            return;
        }
    }
    
    // Update display size
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)width, (float)height);
}

JNIEXPORT void JNICALL
Java_com_visualgui_NativeBridge_onDrawFrame(JNIEnv* env, jobject thiz) {
    if (!g_GUI) return;

    // Clear screen with a dark background
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render GUI
    g_GUI->Render();
}

JNIEXPORT void JNICALL
Java_com_visualgui_NativeBridge_onTouchEvent(JNIEnv* env, jobject thiz, 
                                              jint action, jfloat x, jfloat y, jint pointerId) {
    if (!g_GUI) return;
    
    g_GUI->ProcessTouchEvent(action & 0xFF, x, y);
}

} // extern "C"
