#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Предварительные объявления
class Projectile;
class GameManager;
class Meteor;

class Player {
private:
    string position;
    string sprite;
    string rect;
    int speed;
    bool is_alive;
    float shoot_cooldown;
    int score;  // Добавляем счет игрока

    // Агрегация: Player создает снаряды, но не владеет их временем жизни полностью
    vector<Projectile*> projectiles;

    // Ссылка на GameManager для взаимодействия
    GameManager* game_manager;

public:
    Player();
    Player(GameManager* gm);
    Player(const Player& other);
    ~Player();

    void Move(const string& mouse_pos);
    void Shoot();
    void TakeDamage();
    void Update();
    void Draw();

    // Перегрузка оператора + для добавления очков при попадании по метеору
    Player& operator+(Meteor* meteor);

    // Методы для управления снарядами
    void AddProjectile(Projectile* projectile);
    void RemoveProjectile(Projectile* projectile);

    // Геттер для счета
    int GetScore() const { return score; }

    // Работа со строками
    string GetPlayerInfo() const;
};