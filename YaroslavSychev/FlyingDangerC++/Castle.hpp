#ifndef CASTLE_HPP
#define CASTLE_HPP

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

    void take_damage(int amount);
    bool is_destroyed();
    void draw();

    // Геттеры для доступа к состоянию
    int getHealth() const { return health; }
    int getMaxHealth() const { return max_health; }
};

#endif