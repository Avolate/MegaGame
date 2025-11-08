#include "Enemy.hpp"
#include "GameManager.hpp"
#include "Castle.hpp"

Enemy::Enemy() : health(50), max_health(50), speed(2), position(""), sprite(""), rect(""), game_manager(nullptr) {
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

void Enemy::attackCastle(Castle* castle) {
    if (castle && isAlive()) {
        cout << "Враг атакует замок!" << endl;
        castle->take_damage(10);
    }
}