#ifndef ESP_H
#define ESP_H

#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include <jni.h>
#include <android/log.h>
#include "Vector.h"
#include "Player.h"

// ESP Configuration
struct ESPConfig {
    bool enabled;
    bool box;
    bool fill;
    bool healthBar;
    bool healthAmount;
    bool name;
    bool weaponIcon;
    bool traces;
    bool skeleton;
    float thickness;
    float rounding;
    
    // Colors
    struct {
        float r, g, b, a;
    } playerColor;
    
    struct {
        float r, g, b, a;
    } enemyColor;
};

class ESP {
private:
    ESPConfig config;
    
    // Helper functions
    void DrawBox(Vector2 topLeft, Vector2 bottomRight, float* color);
    void DrawFilledBox(Vector2 topLeft, Vector2 bottomRight, float* color);
    void DrawLine(Vector2 from, Vector2 to, float* color, float width);
    void DrawText(Vector2 position, const char* text, float* color);
    void DrawHealthBar(Vector2 position, float health, float maxHealth);
    void DrawSkeleton(Player* player);
    
    bool WorldToScreen(Vector3 worldPos, Vector2* screenPos);
    bool GetBoundingBox(Player* player, Vector2* topLeft, Vector2* bottomRight);
    
public:
    ESP();
    ~ESP();
    
    void Init();
    void Render();
    void DrawPlayers();
    void DrawPlayer(Player* player);
    void DrawWeapons();
    void DrawGrenades();
    
    void SetConfig(ESPConfig newConfig);
    ESPConfig GetConfig();
    
    void Toggle();
    bool IsEnabled();
};

extern ESP* g_ESP;

#endif // ESP_H
