#ifndef ENEMY_HPP
#define ENEMY_HPP

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
    virtual ~Enemy() = default;

    virtual void move() = 0;
    virtual void take_damage(int amount) = 0;
    virtual bool check_collision(const string& target) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    // Общие методы для всех врагов
    void attackCastle(Castle* castle);
    bool isAlive() const { return health > 0; }

    // Виртуальный метод для проверки границ
    virtual void check_boundaries() {
        cout << "Базовый метод check_boundaries() класса Enemy" << endl;
    }

    // Геттер для max_health
    int getMaxHealth() const { return max_health; }
};

#endif