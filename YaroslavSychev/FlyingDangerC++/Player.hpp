#ifndef PLAYER_HPP
#define PLAYER_HPP

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

    void move(const string& mouse_pos);
    void shoot();
    void take_damage();
    void update();
    void draw();

    // Методы для управления снарядами
    void addProjectile(Projectile* projectile);
    void removeProjectile(Projectile* projectile);
};

#endif