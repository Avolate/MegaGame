#pragma once

#include "Enemy.hpp"
#include <iostream>
using namespace std;

class Boss : public Enemy {
private:
    int phase;
    int size;
    int damage;
    // Статическое поле - счетчик всех созданных боссов
    static int totalBossCount;

    // Статическое поле - максимально допустимое здоровье босса
    static const int MAX_BOSS_HEALTH = 1000;

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

    // Демонстрация разумного использования this
    Boss* SetPhase(int newPhase);
    Boss* SetSize(int newSize);

    // Дружественная функция для анализа босса
    friend void AnalyzeBoss(const Boss& boss);

    // Статический метод - проверка допустимости здоровья
    static bool IsValidHealth(int health);

    // Перегрузка оператора << для уменьшения размера при получении урона
    friend ostream& operator<<(ostream& os, Boss& boss);

    // Геттеры
    int GetPhase() const { return phase; }
    int GetSize() const { return size; }
    int GetDamage() const { return damage; }
};