#ifndef METEOR_HPP
#define METEOR_HPP

#include "Enemy.hpp"
#include <iostream>
using namespace std;

// Предварительное объявление
class GameManager;

class Meteor : public Enemy {
private:
    int size;
    int damage;

public:
    Meteor();
    Meteor(int hp, int spd, int sz, int dmg);
    Meteor(int hp, int spd, int sz, int dmg, GameManager* gm);
    ~Meteor();

    void move() override;
    void take_damage(int amount) override;
    bool check_collision(const string& target) override;
    void update() override;
    void draw() override;

    void apply_damage(int amount);
    void check_boundaries(); // ДОБАВЛЕН НОВЫЙ МЕТОД

    // Геттеры
    int getSize() const { return size; }
    int getDamage() const { return damage; }
};

#endif