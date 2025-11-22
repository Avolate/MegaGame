#pragma once

#include "Enemy.hpp"
#include <iostream>
using namespace std;

class Boss : public Enemy {
private:
    int phase;
    int size;
    int damage;
    // Статическое поле - максимальное здоровье босса для всей игры
    static const int MAX_BOSS_HEALTH;

    // Статическое поле - флаг, был ли босс уже создан (только один босс в игре)
    static bool bossCreated;

public:
    Boss();
    Boss(int hp, int spd, int ph, int sz, int dmg);
    Boss(int hp, int spd, int ph, int sz, int dmg, GameManager* gm);
    Boss(const Boss& other);
    ~Boss();

    void Move() override;
    void TakeDamage(int amount) override;
    bool CheckCollision(const string& target) override;
    void Update() override;
    void Draw() override;
    void ApplyDamage(int amount);
    void ChangePhase();

    // Метод с использованием this для цепочки вызовов
    Boss* SetPhase(int newPhase);

    // Статический метод для проверки возможности создания босса
    static bool CanCreateBoss();

    // Дружественная функция для анализа босса
    friend void AnalyzeBoss(const Boss& boss);

    // Перегрузка оператора << для уменьшения размера при получении урона
    friend ostream& operator<<(ostream& os, Boss& boss);

    // Геттеры
    int GetPhase() const { return phase; }
    int GetSize() const { return size; }
    int GetDamage() const { return damage; }
};