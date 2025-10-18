#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Предварительное объявление
class Projectile;
class GameManager;

class Player {
private:
    string position;
    string sprite;
    string rect;
    int speed;
    bool is_alive;
    float shoot_cooldown;

    // Агрегация: Player создает снаряды, но не владеет их временем жизни полностью
    vector<Projectile*> projectiles;

    // Ссылка на GameManager для взаимодействия
    GameManager* game_manager;

public:
    Player();
    Player(GameManager* gm);
    ~Player();

    void Move(const string& mouse_pos);
    void Shoot();
    void TakeDamage();
    void Update();
    void Draw();

    // Методы для управления снарядами
    void AddProjectile(Projectile* projectile);
    void RemoveProjectile(Projectile* projectile);
};

//#endif