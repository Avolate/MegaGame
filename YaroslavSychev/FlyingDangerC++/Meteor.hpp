#pragma once

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
    Meteor(const Meteor& other);
    ~Meteor();

    void Move() override;
    void TakeDamage(int amount) override;
    bool CheckCollision(const string& target) override;
    void Update() override;
    void Draw() override;

    void apply_damage(int amount);
    void check_boundaries(); // ДОБАВЛЕН НОВЫЙ МЕТОД

    // Геттеры
    int getSize() const { return size; }
    int getDamage() const { return damage; }
};

//#endif