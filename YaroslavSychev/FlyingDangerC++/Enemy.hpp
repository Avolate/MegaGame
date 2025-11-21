#pragma once

#include <iostream>
#include <string>
using namespace std;

// Предварительное объявление
class GameManager;
class Castle;

class Enemy {
protected:
    int health;
    int max_health;
    int speed;
    string position;
    string sprite;
    string rect;

    // Ссылка на GameManager для взаимодействия
    GameManager* game_manager;

public:
    Enemy();
    Enemy(int hp, int spd);
    Enemy(int hp, int spd, GameManager* gm);
    Enemy(const Enemy& other);
    virtual ~Enemy() = default;

    virtual void Move() = 0;
    virtual void TakeDamage(int amount) = 0;
    virtual bool CheckCollision(const string& target) = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    // Общие методы для всех врагов
    void AttackCastle(Castle* castle);
    bool IsAlive() const { return health > 0; }

    // Виртуальный метод для проверки границ
    virtual void check_boundaries() {
        cout << "Базовый метод check_boundaries() класса Enemy" << endl;
    }

    // Геттер для max_health
    int GetMaxHealth() const { return max_health; }

    // Геттеры для доступа к полям
    int GetHealth() const { return health; }
    int GetSpeed() const { return speed; }
    const string& GetPosition() const { return position; }

    // Работа со строками
    void SetPosition(const string& newPosition);
};