#ifndef AIMBOT_H
#define AIMBOT_H

#include "Player.h"
#include "Vector.h"

struct AimbotConfig {
    bool enabled;
    bool fovCheck;
    bool drawFov;
    bool fireCheck;
    bool autoFire;
    bool untouchableCheck;
    bool silent;
    
    struct {
        bool head;
        bool neck;
        bool stomach;
        bool hands;
        bool legs;
        bool foots;
    } bones;
    
    struct {
        float damage;
        float angle;
    } boneFilter;
    
    float speed;
    float hitChance;
    float fov;
};

class Aimbot {
private:
    AimbotConfig config;
    Player* currentTarget;
    
    Player* FindBestTarget();
    int GetBestBone(Player* player);
    bool IsTargetValid(Player* player);
    float GetDistance(Player* player);
    float GetFOV(Player* player, int bone);
    
public:
    Aimbot();
    ~Aimbot();
    
    void Init();
    void Update();
    void AimAt(Player* player, int bone);
    
    void SetConfig(AimbotConfig newConfig);
    AimbotConfig GetConfig();
    
    void Toggle();
    bool IsEnabled();
};

extern Aimbot* g_Aimbot;

#endif // AIMBOT_H
