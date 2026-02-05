#ifndef PLAYER_H
#define PLAYER_H

#include "Vector.h"
#include <string>

// Forward declarations
class Transform;
class GameObject;
class Weapon;

class Player {
private:
    uintptr_t instance;
    
public:
    Player(uintptr_t addr);
    
    bool IsValid() const;
    bool IsDead() const;
    bool IsLocal() const;
    
    int GetTeam() const;
    float GetHealth() const;
    float GetMaxHealth() const;
    const char* GetName() const;
    
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    Vector3 GetBonePosition(int boneIndex) const;
    
    Weapon* GetCurrentWeapon() const;
    Transform* GetTransform() const;
};

class Weapon {
private:
    uintptr_t instance;
    
public:
    Weapon(uintptr_t addr);
    
    bool IsValid() const;
    const char* GetName() const;
    int GetAmmo() const;
    int GetMaxAmmo() const;
    Vector3 GetPosition() const;
};

class Grenade {
private:
    uintptr_t instance;
    
public:
    Grenade(uintptr_t addr);
    
    bool IsValid() const;
    Vector3 GetPosition() const;
    float GetTimer() const;
    int GetType() const; // 0=frag, 1=flash, 2=smoke
};

#endif // PLAYER_H
