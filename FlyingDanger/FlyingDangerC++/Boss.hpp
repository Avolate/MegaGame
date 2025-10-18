#ifndef BOSS_HPP
#define BOSS_HPP

#include "Enemy.hpp"
#include <iostream>
using namespace std;

// Предварительное объявление
class GameManager;

class Boss : public Enemy {
private:
    int phase;
    int size;
    int damage;

public:
    Boss();
    Boss(int hp, int spd, int ph, int sz, int dmg);
    Boss(int hp, int spd, int ph, int sz, int dmg, GameManager* gm);
    ~Boss();

    void move() override;
    void take_damage(int amount) override;
    bool check_collision(const string& target) override;
    void update() override;
    void draw() override;

    void apply_damage(int amount);
    void change_phase();

    // Геттеры
    int getPhase() const { return phase; }
    int getSize() const { return size; }
    int getDamage() const { return damage; }
};

#endif