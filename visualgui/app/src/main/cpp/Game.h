#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Vector.h"
#include <vector>

namespace Game {
    // Initialization
    bool Init();
    void Shutdown();
    
    // Player management
    Player* GetLocalPlayer();
    std::vector<Player*> GetPlayers();
    std::vector<Weapon*> GetWeapons();
    std::vector<Grenade*> GetGrenades();
    
    // Camera & Screen
    Matrix4x4 GetViewMatrix();
    bool WorldToScreen(Vector3 worldPos, Vector2* screenPos);
    float GetScreenWidth();
    float GetScreenHeight();
    
    // Game state
    bool IsInGame();
    int GetGameMode();
    float GetGameTime();
    
    // Offsets (need to be updated per game version)
    namespace Offsets {
        extern uintptr_t PlayerList;
        extern uintptr_t LocalPlayer;
        extern uintptr_t ViewMatrix;
        extern uintptr_t GameMode;
        extern uintptr_t GameTime;
        
        // Player offsets
        extern uintptr_t PlayerHealth;
        extern uintptr_t PlayerMaxHealth;
        extern uintptr_t PlayerTeam;
        extern uintptr_t PlayerName;
        extern uintptr_t PlayerTransform;
        extern uintptr_t PlayerWeapon;
        extern uintptr_t PlayerIsDead;
        
        // Transform offsets
        extern uintptr_t TransformPosition;
        extern uintptr_t TransformRotation;
        extern uintptr_t TransformBones;
        
        // Weapon offsets
        extern uintptr_t WeaponName;
        extern uintptr_t WeaponAmmo;
        extern uintptr_t WeaponMaxAmmo;
        extern uintptr_t WeaponPosition;
    }
}

#endif // GAME_H
