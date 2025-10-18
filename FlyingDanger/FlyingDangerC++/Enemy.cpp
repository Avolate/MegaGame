#include "Enemy.hpp"
#include "GameManager.hpp"
#include "Castle.hpp"

int currentMeteorHealth = 100;
int maxMeteorHealth = 100;
int defaultSpeed = 2;
int defaultDamage = 10;


Enemy::Enemy() : health(currentMeteorHealth), max_health(maxMeteorHealth), speed(defaultSpeed), position(""), sprite(""), rect(""), game_manager(nullptr) {
    cout << "Объект класса Enemy создан" << endl;
}

Enemy::Enemy(int hp, int spd) : health(hp), max_health(hp), speed(spd), position(""), sprite(""), rect(""),
game_manager(nullptr) {
    cout << "Объект класса Enemy создан с параметрами" << endl;
}

Enemy::Enemy(int hp, int spd, GameManager* gm) : health(hp), max_health(hp), speed(spd), position(""),
sprite(""), rect(""), game_manager(gm) {
    cout << "Объект класса Enemy создан с ссылкой на GameManager" << endl;
}

void Enemy::AttackCastle(Castle* castle) {
    if (castle && IsAlive()) {
        cout << "Враг атакует замок!" << endl;
        castle->TakeDamage(defaultDamage);
    }
}