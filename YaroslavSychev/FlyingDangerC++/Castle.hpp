#pragma once

#include <iostream>
#include <string>
using namespace std;

class Castle {
private:
    int health;
    int max_health;
    string position;
    string sprite;
    string rect;

public:
    Castle();
    Castle(int max_hp);
    Castle(const Castle& other);
    ~Castle();

    void TakeDamage(int amount);
    bool IsDestroyed();
    void Draw();

    // Перегрузка оператора - для уменьшения здоровья замка
    Castle& operator-(int damage);

    // Дружественная функция для замка
    friend void RepairCastle(Castle& castle, int amount);

    // Геттеры для доступа к состоянию
    int GetHealth() const { return health; }
    int GetMaxHealth() const { return max_health; }

    // Работа со строками
    void SetPosition(const string& newPosition);
};