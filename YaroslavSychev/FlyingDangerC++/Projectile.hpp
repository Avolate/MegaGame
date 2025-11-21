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

    // Статический счетчик активных снарядов
    static int active_projectiles;
    static const int MAX_PROJECTILES;

public:
    Projectile();
    Projectile(const string& pos, const string& dir, int dmg);
    Projectile(const string& pos, const string& dir, int dmg, Player* player);
    Projectile(const Projectile& other);
    ~Projectile();

    void Update();
    bool CheckCollision(Enemy* enemy);
    void OnHit();
    void CheckBoundaries();
    void Draw();

    // Перегрузка оператора == для проверки лимита снарядов
    bool operator==(const Projectile& other) const;

    // Геттеры
    bool IsActive() const { return is_active; }
    int GetDamage() const { return damage; }

    // Статические методы для управления лимитом
    static bool CanCreateProjectile() {
        return active_projectiles < MAX_PROJECTILES;
    }

    // Работа со строками
    string GetDescription() const {
        return "Снаряд: урон=" + to_string(damage) + ", активных: " + to_string(active_projectiles);
    }
};