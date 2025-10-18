#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

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

    void update();
    bool check_collision(Enemy* enemy);
    void on_hit();
    void check_boundaries();
    void draw();

    // Геттеры
    bool isActive() const { return is_active; }
    int getDamage() const { return damage; }
};

#endif