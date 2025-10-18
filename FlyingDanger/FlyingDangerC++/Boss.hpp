#pragma once

#include "Enemy.hpp"
#include <iostream>
using namespace std;

// Предварительное объявление
// class GameManager;

class Boss : public Enemy {
private:
    int phase;
    int size;
    int damage;

public:
    Boss();
    Boss(int hp, int spd, int ph, int sz, int dmg);
    Boss(int hp, int spd, int ph, int sz, int dmg, GameManager* gm);
    ~Boss();

    void Move() override;
    void TakeDamage(int amount) override;
    bool CheckCollision(const string& target) override;
    void Update() override;
    void Draw() override;

    void ApplyDamage(int amount);
    void ChangePhase();

    // Геттеры
    int GetPhase() const { return phase; }
    int GetSize() const { return size; }
    int GetDamage() const { return damage; }
};

//#endif