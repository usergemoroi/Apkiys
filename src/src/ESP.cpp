#include "ESP.h"
#include "Game.h"
#include "Drawing.h"
#include <cmath>
#include <android/log.h>
#include <cstdio>

ESP* g_ESP = nullptr;

ESP::ESP() {
    config.enabled = true;
    config.box = true;
    config.fill = false;
    config.healthBar = true;
    config.healthAmount = true;
    config.name = true;
    config.weaponIcon = true;
    config.traces = false;
    config.skeleton = true;
    config.thickness = 2.0f;
    config.rounding = 0.0f;
    
    // Player color (green)
    config.playerColor.r = 0.0f;
    config.playerColor.g = 1.0f;
    config.playerColor.b = 0.0f;
    config.playerColor.a = 1.0f;
    
    // Enemy color (red)
    config.enemyColor.r = 1.0f;
    config.enemyColor.g = 0.0f;
    config.enemyColor.b = 0.0f;
    config.enemyColor.a = 1.0f;
}

ESP::~ESP() {
}

void ESP::Init() {
    __android_log_print(ANDROID_LOG_INFO, "ESP", "Initialized");
}

void ESP::Render() {
    if (!config.enabled) return;
    
    DrawPlayers();
    
    if (config.weaponIcon) {
        DrawWeapons();
    }
    
    DrawGrenades();
}

void ESP::DrawPlayers() {
    auto players = Game::GetPlayers();
    
    for (auto player : players) {
        if (player && player->IsValid() && !player->IsDead()) {
            DrawPlayer(player);
        }
    }
}

void ESP::DrawPlayer(Player* player) {
    if (!player) return;
    
    Vector2 topLeft, bottomRight;
    if (!GetBoundingBox(player, &topLeft, &bottomRight)) {
        return;
    }
    
    bool isEnemy = player->GetTeam() != Game::GetLocalPlayer()->GetTeam();
    float* color = isEnemy ? (float*)&config.enemyColor : (float*)&config.playerColor;
    
    // Draw box
    if (config.box) {
        DrawBox(topLeft, bottomRight, color);
    }
    
    // Draw filled box
    if (config.fill) {
        float fillColor[4] = {color[0], color[1], color[2], color[3] * 0.3f};
        DrawFilledBox(topLeft, bottomRight, fillColor);
    }
    
    // Draw health bar
    if (config.healthBar) {
        Vector2 healthBarPos = {topLeft.x - 6, topLeft.y};
        DrawHealthBar(healthBarPos, player->GetHealth(), player->GetMaxHealth());
    }
    
    // Draw health amount
    if (config.healthAmount) {
        char healthText[32];
        snprintf(healthText, sizeof(healthText), "%d HP", (int)player->GetHealth());
        Vector2 textPos = {topLeft.x, topLeft.y - 15};
        DrawText(textPos, healthText, color);
    }
    
    // Draw name
    if (config.name) {
        Vector2 namePos = {topLeft.x, bottomRight.y + 5};
        DrawText(namePos, player->GetName(), color);
    }
    
    // Draw skeleton
    if (config.skeleton) {
        DrawSkeleton(player);
    }
    
    // Draw traces
    if (config.traces) {
        Vector2 screenCenter = {Game::GetScreenWidth() / 2.0f, Game::GetScreenHeight()};
        Vector2 playerFeet = {(topLeft.x + bottomRight.x) / 2.0f, bottomRight.y};
        DrawLine(screenCenter, playerFeet, color, config.thickness);
    }
}

void ESP::DrawWeapons() {
    auto weapons = Game::GetWeapons();
    
    for (auto weapon : weapons) {
        if (weapon && weapon->IsValid()) {
            Vector3 worldPos = weapon->GetPosition();
            Vector2 screenPos;
            
            if (WorldToScreen(worldPos, &screenPos)) {
                float color[4] = {1.0f, 1.0f, 0.0f, 1.0f}; // Yellow
                
                DrawText(screenPos, weapon->GetName(), color);
                
                char ammoText[32];
                snprintf(ammoText, sizeof(ammoText), "Ammo: %d", weapon->GetAmmo());
                Vector2 ammoPos = {screenPos.x, screenPos.y + 15};
                DrawText(ammoPos, ammoText, color);
            }
        }
    }
}

void ESP::DrawGrenades() {
    auto grenades = Game::GetGrenades();
    
    for (auto grenade : grenades) {
        if (grenade && grenade->IsValid()) {
            Vector3 worldPos = grenade->GetPosition();
            Vector2 screenPos;
            
            if (WorldToScreen(worldPos, &screenPos)) {
                float color[4] = {1.0f, 0.5f, 0.0f, 1.0f}; // Orange
                
                // Draw circle
                Drawing::DrawCircle(screenPos, 30.0f, color, config.thickness);
                
                // Draw timer
                char timerText[32];
                snprintf(timerText, sizeof(timerText), "%.1f", grenade->GetTimer());
                DrawText(screenPos, timerText, color);
            }
        }
    }
}

void ESP::DrawBox(Vector2 topLeft, Vector2 bottomRight, float* color) {
    Drawing::DrawRect(topLeft, bottomRight, color, config.thickness, config.rounding);
}

void ESP::DrawFilledBox(Vector2 topLeft, Vector2 bottomRight, float* color) {
    Drawing::DrawFilledRect(topLeft, bottomRight, color);
}

void ESP::DrawLine(Vector2 from, Vector2 to, float* color, float width) {
    Drawing::DrawLine(from, to, color, width);
}

void ESP::DrawText(Vector2 position, const char* text, float* color) {
    Drawing::DrawText(position, text, color);
}

void ESP::DrawHealthBar(Vector2 position, float health, float maxHealth) {
    float barHeight = 60.0f;
    float barWidth = 4.0f;
    float healthPercent = health / maxHealth;
    
    // Background (black)
    float bgColor[4] = {0.0f, 0.0f, 0.0f, 0.5f};
    Vector2 bgTopLeft = position;
    Vector2 bgBottomRight = {position.x + barWidth, position.y + barHeight};
    DrawFilledBox(bgTopLeft, bgBottomRight, bgColor);
    
    // Health bar (gradient from red to green)
    float healthColor[4];
    healthColor[0] = 1.0f - healthPercent; // Red
    healthColor[1] = healthPercent;        // Green
    healthColor[2] = 0.0f;                 // Blue
    healthColor[3] = 1.0f;                 // Alpha
    
    Vector2 hpTopLeft = {position.x, position.y + barHeight * (1.0f - healthPercent)};
    Vector2 hpBottomRight = {position.x + barWidth, position.y + barHeight};
    DrawFilledBox(hpTopLeft, hpBottomRight, healthColor);
    
    // Border (white)
    float borderColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    DrawBox(bgTopLeft, bgBottomRight, borderColor);
}

void ESP::DrawSkeleton(Player* player) {
    if (!player) return;
    
    // Bone indices
    enum Bone {
        HEAD = 0,
        NECK = 1,
        CHEST = 2,
        STOMACH = 3,
        PELVIS = 4,
        LEFT_SHOULDER = 5,
        LEFT_ELBOW = 6,
        LEFT_HAND = 7,
        RIGHT_SHOULDER = 8,
        RIGHT_ELBOW = 9,
        RIGHT_HAND = 10,
        LEFT_HIP = 11,
        LEFT_KNEE = 12,
        LEFT_FOOT = 13,
        RIGHT_HIP = 14,
        RIGHT_KNEE = 15,
        RIGHT_FOOT = 16,
        BONE_MAX
    };
    
    Vector2 bones[BONE_MAX];
    bool visible[BONE_MAX];
    
    // Get all bone positions
    for (int i = 0; i < BONE_MAX; i++) {
        Vector3 bonePos = player->GetBonePosition(i);
        visible[i] = WorldToScreen(bonePos, &bones[i]);
    }
    
    bool isEnemy = player->GetTeam() != Game::GetLocalPlayer()->GetTeam();
    float* color = isEnemy ? (float*)&config.enemyColor : (float*)&config.playerColor;
    
    // Draw skeleton lines
    auto drawBone = [&](int from, int to) {
        if (visible[from] && visible[to]) {
            DrawLine(bones[from], bones[to], color, config.thickness);
        }
    };
    
    // Head to body
    drawBone(HEAD, NECK);
    drawBone(NECK, CHEST);
    drawBone(CHEST, STOMACH);
    drawBone(STOMACH, PELVIS);
    
    // Left arm
    drawBone(CHEST, LEFT_SHOULDER);
    drawBone(LEFT_SHOULDER, LEFT_ELBOW);
    drawBone(LEFT_ELBOW, LEFT_HAND);
    
    // Right arm
    drawBone(CHEST, RIGHT_SHOULDER);
    drawBone(RIGHT_SHOULDER, RIGHT_ELBOW);
    drawBone(RIGHT_ELBOW, RIGHT_HAND);
    
    // Left leg
    drawBone(PELVIS, LEFT_HIP);
    drawBone(LEFT_HIP, LEFT_KNEE);
    drawBone(LEFT_KNEE, LEFT_FOOT);
    
    // Right leg
    drawBone(PELVIS, RIGHT_HIP);
    drawBone(RIGHT_HIP, RIGHT_KNEE);
    drawBone(RIGHT_KNEE, RIGHT_FOOT);
}

bool ESP::WorldToScreen(Vector3 worldPos, Vector2* screenPos) {
    return Game::WorldToScreen(worldPos, screenPos);
}

bool ESP::GetBoundingBox(Player* player, Vector2* topLeft, Vector2* bottomRight) {
    Vector3 head = player->GetBonePosition(0);  // Head
    Vector3 feet = player->GetPosition();
    
    Vector2 headScreen, feetScreen;
    if (!WorldToScreen(head, &headScreen) || !WorldToScreen(feet, &feetScreen)) {
        return false;
    }
    
    float height = abs(feetScreen.y - headScreen.y);
    float width = height * 0.4f;
    
    topLeft->x = headScreen.x - width / 2.0f;
    topLeft->y = headScreen.y;
    
    bottomRight->x = headScreen.x + width / 2.0f;
    bottomRight->y = feetScreen.y;
    
    return true;
}

void ESP::SetConfig(ESPConfig newConfig) {
    config = newConfig;
}

ESPConfig ESP::GetConfig() {
    return config;
}

void ESP::Toggle() {
    config.enabled = !config.enabled;
}

bool ESP::IsEnabled() {
    return config.enabled;
}
