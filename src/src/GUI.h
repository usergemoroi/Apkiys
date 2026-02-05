#ifndef GUI_H
#define GUI_H

#include <jni.h>
#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"

class GUI {
private:
    bool initialized;
    bool visible;
    
    // Tab indices
    int currentTab;
    
    enum Tab {
        TAB_AIMBOT = 0,
        TAB_VISUALS,
        TAB_EXPLOITS,
        TAB_SKINS,
        TAB_CONFIG,
        TAB_SETTINGS,
        TAB_COUNT
    };
    
    void DrawAimbotTab();
    void DrawVisualsTab();
    void DrawExploitsTab();
    void DrawSkinsTab();
    void DrawConfigTab();
    void DrawSettingsTab();
    
    void ApplyStyle();
    
public:
    GUI();
    ~GUI();
    
    bool Init();
    void Shutdown();
    void Render();
    bool ProcessEvent(AInputEvent* event);
    
    void Toggle();
    bool IsVisible();
    void SetVisible(bool state);
};

extern GUI* g_GUI;

#endif // GUI_H
