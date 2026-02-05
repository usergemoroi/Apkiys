#include "Game.h"

namespace Game {
    namespace Offsets {
        uintptr_t PlayerList = 0;
        uintptr_t LocalPlayer = 0;
        uintptr_t ViewMatrix = 0;
        uintptr_t GameMode = 0;
        uintptr_t GameTime = 0;
        uintptr_t PlayerHealth = 0;
        uintptr_t PlayerMaxHealth = 0;
        uintptr_t PlayerTeam = 0;
        uintptr_t PlayerName = 0;
        uintptr_t PlayerTransform = 0;
        uintptr_t PlayerWeapon = 0;
        uintptr_t PlayerIsDead = 0;
        uintptr_t TransformPosition = 0;
        uintptr_t TransformRotation = 0;
        uintptr_t TransformBones = 0;
        uintptr_t WeaponName = 0;
        uintptr_t WeaponAmmo = 0;
        uintptr_t WeaponMaxAmmo = 0;
        uintptr_t WeaponPosition = 0;
    }

    bool Init() {
        return true;
    }

    void Shutdown() {
        // Shutdown
    }

    Player* GetLocalPlayer() {
        static Player localPlayer(0);
        return &localPlayer;
    }

    std::vector<Player*> GetPlayers() {
        static std::vector<Player*> players;
        return players;
    }

    std::vector<Weapon*> GetWeapons() {
        static std::vector<Weapon*> weapons;
        return weapons;
    }

    std::vector<Grenade*> GetGrenades() {
        static std::vector<Grenade*> grenades;
        return grenades;
    }

    Matrix4x4 GetViewMatrix() {
        static Matrix4x4 matrix;
        return matrix;
    }

    bool WorldToScreen(Vector3 worldPos, Vector2* screenPos) {
        if (screenPos) {
            screenPos->x = worldPos.x;
            screenPos->y = worldPos.y;
        }
        return true;
    }

    float GetScreenWidth() {
        return 1920.0f;
    }

    float GetScreenHeight() {
        return 1080.0f;
    }

    bool IsInGame() {
        return true;
    }

    int GetGameMode() {
        return 0;
    }

    float GetGameTime() {
        return 0.0f;
    }
}