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
    ~Castle();

    void TakeDamage(int amount);
    bool IsDestroyed();
    void Draw();

    // Геттеры для доступа к состоянию
    int GetHealth() const { return health; }
    int GetMaxHealth() const { return max_health; }
};

//#endif