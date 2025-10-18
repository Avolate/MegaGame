#pragma once

#include <iostream>
#include <string>
using namespace std;

// Предварительное объявление
class Enemy;
class Player;

class Projectile {
private:
    string position;
    string direction;
    int speed;
    int damage;
    string rect;
    bool is_active;

    // Ссылка на игрока, который выпустил снаряд
    Player* owner;

public:
    Projectile();
    Projectile(const string& pos, const string& dir, int dmg);
    Projectile(const string& pos, const string& dir, int dmg, Player* player);
    ~Projectile();

    void Update();
    bool CheckCollision(Enemy* enemy);
    void OnHit();
    void CheckBoundaries();
    void Draw();

    // Геттеры
    bool IsActive() const { return is_active; }
    int GetDamage() const { return damage; }
};

//#endif