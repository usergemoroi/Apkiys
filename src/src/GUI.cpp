#include "GUI.h"
#include "ESP.h"
#include "Aimbot.h"
#include "Config.h"
#include <string>
#include <android/log.h>
#include <cstdio>

GUI* g_GUI = nullptr;

GUI::GUI() {
    initialized = false;
    visible = true;
    currentTab = TAB_VISUALS;
}

GUI::~GUI() {
    Shutdown();
}

bool GUI::Init() {
    if (initialized) return true;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
    ApplyStyle();
    
    initialized = true;
    __android_log_print(ANDROID_LOG_INFO, "GUI", "Initialized");
    return true;
}

void GUI::Shutdown() {
    if (!initialized) return;
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    
    initialized = false;
}

void GUI::Render() {
    if (!initialized || !visible) return;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    // Main menu window
    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Standoff 2 Mod Menu", &visible, ImGuiWindowFlags_NoCollapse);
    
    // Tab buttons
    if (ImGui::BeginTabBar("MainTabs")) {
        if (ImGui::BeginTabItem("Aimbot")) {
            currentTab = TAB_AIMBOT;
            DrawAimbotTab();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Visuals")) {
            currentTab = TAB_VISUALS;
            DrawVisualsTab();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Exploits")) {
            currentTab = TAB_EXPLOITS;
            DrawExploitsTab();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Skins")) {
            currentTab = TAB_SKINS;
            DrawSkinsTab();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Config")) {
            currentTab = TAB_CONFIG;
            DrawConfigTab();
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Settings")) {
            currentTab = TAB_SETTINGS;
            DrawSettingsTab();
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }
    
    ImGui::End();
    
    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::DrawAimbotTab() {
    auto config = g_Aimbot->GetConfig();
    
    ImGui::SeparatorText("Main");
    ImGui::Checkbox("Enable", &config.enabled);
    ImGui::Checkbox("FOV Check", &config.fovCheck);
    ImGui::Checkbox("Draw Fov", &config.drawFov);
    ImGui::Checkbox("Fire Check", &config.fireCheck);
    ImGui::Checkbox("Auto Fire", &config.autoFire);
    ImGui::Checkbox("Untouchable Check", &config.untouchableCheck);
    ImGui::Checkbox("Silent", &config.silent);
    
    ImGui::SeparatorText("Target Bones");
    ImGui::Checkbox("Head", &config.bones.head);
    ImGui::Checkbox("Neck", &config.bones.neck);
    ImGui::Checkbox("Stomach", &config.bones.stomach);
    ImGui::Checkbox("Hands", &config.bones.hands);
    ImGui::Checkbox("Legs", &config.bones.legs);
    ImGui::Checkbox("Foots", &config.bones.foots);
    
    ImGui::SeparatorText("Settings");
    ImGui::SliderFloat("Speed", &config.speed, 1.0f, 100.0f);
    ImGui::SliderFloat("Hit Chance", &config.hitChance, 0.0f, 100.0f);
    ImGui::SliderFloat("FOV", &config.fov, 10.0f, 360.0f);
    
    ImGui::Text("Bone Filter");
    ImGui::SliderFloat("Damage", &config.boneFilter.damage, 0.0f, 100.0f);
    ImGui::SliderFloat("Angle", &config.boneFilter.angle, 0.0f, 180.0f);
    
    g_Aimbot->SetConfig(config);
}

void GUI::DrawVisualsTab() {
    auto espConfig = g_ESP->GetConfig();
    
    ImGui::SeparatorText("Player ESP");
    ImGui::Checkbox("Enable##Player", &espConfig.enabled);
    ImGui::Checkbox("Box", &espConfig.box);
    ImGui::Checkbox("Fill", &espConfig.fill);
    ImGui::Checkbox("Health Bar", &espConfig.healthBar);
    ImGui::Checkbox("Health Amount", &espConfig.healthAmount);
    ImGui::Checkbox("Name", &espConfig.name);
    ImGui::Checkbox("Weapon Icon", &espConfig.weaponIcon);
    ImGui::Checkbox("Traces", &espConfig.traces);
    ImGui::Checkbox("Skeleton", &espConfig.skeleton);
    
    ImGui::SliderFloat("Thickness", &espConfig.thickness, 1.0f, 5.0f);
    ImGui::SliderFloat("Rounding", &espConfig.rounding, 0.0f, 10.0f);
    
    ImGui::SeparatorText("Chams");
    static bool chamsEnabled = false;
    static int chamsType = 0;
    ImGui::Checkbox("Enable##Chams", &chamsEnabled);
    ImGui::Combo("Type", &chamsType, "Flat\0Wireframe\0Glow\0");
    
    ImGui::SeparatorText("World");
    static bool bulletTracer = false;
    static bool fog = false;
    static float fogStart = 0.0f;
    static float fogEnd = 1000.0f;
    
    ImGui::Checkbox("Bullet Tracer", &bulletTracer);
    ImGui::Checkbox("Fog", &fog);
    if (fog) {
        ImGui::SliderFloat("Fog Start", &fogStart, 0.0f, 1000.0f);
        ImGui::SliderFloat("Fog End", &fogEnd, 0.0f, 5000.0f);
    }
    
    ImGui::SeparatorText("Sky");
    static float atmosphereThickness = 1.0f;
    static float exposure = 1.0f;
    ImGui::SliderFloat("Atmosphere Thickness", &atmosphereThickness, 0.0f, 5.0f);
    ImGui::SliderFloat("Exposure", &exposure, 0.0f, 5.0f);
    
    g_ESP->SetConfig(espConfig);
}

void GUI::DrawExploitsTab() {
    ImGui::SeparatorText("Weapon");
    static bool fireRate = false;
    static bool infinityAmmo = false;
    ImGui::Checkbox("Fire Rate", &fireRate);
    ImGui::Checkbox("Infinity Ammo", &infinityAmmo);
    
    ImGui::SeparatorText("Host");
    ImGui::Text("You need to be host for these features!");
    static bool autowin = false;
    static bool crashHost = false;
    ImGui::Checkbox("Autowin", &autowin);
    ImGui::Checkbox("Crash Host", &crashHost);
    
    ImGui::SeparatorText("Bomb");
    static bool getBomb = false;
    static bool autoWinBomb = false;
    ImGui::Checkbox("Get Bomb", &getBomb);
    ImGui::Checkbox("Auto Win", &autoWinBomb);
    
    ImGui::SeparatorText("Premium");
    static bool tpv = false;
    static bool invisible = false;
    static bool chatSpam = false;
    static bool autoKill = false;
    static bool fastStrafe = false;
    static bool crashEnemies = false;
    static bool crashTeammates = false;
    
    ImGui::Checkbox("TPV", &tpv);
    ImGui::Checkbox("Invisible", &invisible);
    ImGui::Checkbox("Chat Spam", &chatSpam);
    ImGui::Checkbox("Auto Kill", &autoKill);
    ImGui::Checkbox("Fast Strafe", &fastStrafe);
    ImGui::Checkbox("Crash Enemies", &crashEnemies);
    ImGui::Checkbox("Crash Teammates", &crashTeammates);
    
    ImGui::SeparatorText("Movement");
    static bool airJump = false;
    ImGui::Checkbox("Air Jump", &airJump);
}

void GUI::DrawSkinsTab() {
    ImGui::SeparatorText("Skins");
    
    ImGui::Text("Skin Editor");
    if (ImGui::Button("Edit")) {
        ImGui::OpenPopup("Skin Editor");
    }
    
    if (ImGui::BeginPopup("Skin Editor")) {
        ImGui::Text("Add Skin");
        
        static char skinName[128] = "";
        ImGui::InputText("Name", skinName, sizeof(skinName));
        
        static int skinType = 0;
        ImGui::Combo("Type", &skinType, "Weapon\0Gloves\0Sticker\0");
        
        static int stattrack = 0;
        ImGui::InputInt("Stattrack", &stattrack);
        
        static int pattern = 0;
        ImGui::InputInt("Pattern", &pattern);
        
        static int rare = 0;
        ImGui::InputInt("Rare", &rare);
        
        if (ImGui::Button("Apply")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
    
    ImGui::Separator();
    ImGui::Text("Available Skins:");
    ImGui::BeginChild("SkinsList", ImVec2(0, 300), true);
    
    for (int i = 0; i < 50; i++) {
        char label[64];
        snprintf(label, sizeof(label), "Skin #%d", i);
        if (ImGui::Selectable(label)) {
            // Apply skin
        }
    }
    
    ImGui::EndChild();
}

void GUI::DrawConfigTab() {
    ImGui::SeparatorText("Configuration");
    
    static char configName[128] = "default";
    ImGui::InputText("Config Name", configName, sizeof(configName));
    
    if (ImGui::Button("Save Config")) {
        Config::Save(configName);
        __android_log_print(ANDROID_LOG_INFO, "GUI", "Config saved: %s", configName);
    }
    
    ImGui::SameLine();
    
    if (ImGui::Button("Load Config")) {
        Config::Load(configName);
        __android_log_print(ANDROID_LOG_INFO, "GUI", "Config loaded: %s", configName);
    }
    
    ImGui::Separator();
    ImGui::Text("Available Configs:");
    ImGui::BeginChild("ConfigsList", ImVec2(0, 300), true);
    
    auto configs = Config::GetConfigList();
    for (const auto& cfg : configs) {
        char label[128];
        snprintf(label, sizeof(label), "%s (Created by: %s)", cfg.name.c_str(), cfg.creator.c_str());
        if (ImGui::Selectable(label)) {
            Config::Load(cfg.name.c_str());
        }
    }
    
    ImGui::EndChild();
}

void GUI::DrawSettingsTab() {
    ImGui::SeparatorText("General");
    
    static bool showFPS = true;
    ImGui::Checkbox("Show FPS", &showFPS);
    
    static bool antiScreenshot = false;
    ImGui::Checkbox("Anti Screenshot", &antiScreenshot);
    
    ImGui::SeparatorText("Panic Mode");
    if (ImGui::Button("Panic! (Disable All)")) {
        g_ESP->SetConfig({});
        g_Aimbot->SetConfig({});
    }
    
    ImGui::SeparatorText("About");
    ImGui::Text("Standoff 2 Mod Menu");
    ImGui::Text("Version: 1.0.0");
    ImGui::Text("Built: %s %s", __DATE__, __TIME__);
    
    ImGui::Separator();
    ImGui::Text("Developed for educational purposes only");
}

void GUI::ApplyStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    
    // Dark theme with purple accent
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.36f, 0.36f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.20f, 0.20f, 0.75f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.66f, 0.20f, 1.00f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.56f, 0.10f, 1.00f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.66f, 0.20f, 1.00f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.56f, 0.10f, 1.00f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.10f, 1.00f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.56f, 0.10f, 1.00f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.56f, 0.10f, 1.00f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.10f, 1.00f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.56f, 0.10f, 1.00f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.56f, 0.10f, 1.00f, 0.35f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.56f, 0.10f, 1.00f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.56f, 0.10f, 1.00f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
    
    style.WindowRounding = 5.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.ScrollbarRounding = 3.0f;
    style.TabRounding = 3.0f;
}

bool GUI::ProcessEvent(AInputEvent* event) {
    if (!initialized || !visible) return false;
    
    return ImGui_ImplAndroid_HandleInputEvent(event);
}

void GUI::Toggle() {
    visible = !visible;
}

bool GUI::IsVisible() {
    return visible;
}

void GUI::SetVisible(bool state) {
    visible = state;
}
