#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

Projectile::Projectile() : position(""), direction(""), speed(10), damage(10),
rect(""), is_active(true), owner(nullptr) {
    cout << "Объект класса Projectile создан" << endl;
}

Projectile::Projectile(const string& pos, const string& dir, int dmg)
    : position(pos), direction(dir), speed(10), damage(dmg), rect(""),
    is_active(true), owner(nullptr) {
    cout << "Объект класса Projectile создан с параметрами" << endl;
}

Projectile::Projectile(const string& pos, const string& dir, int dmg, Player* player)
    : position(pos), direction(dir), speed(10), damage(dmg), rect(""),
    is_active(true), owner(player) {
    cout << "Объект класса Projectile создан с владельцем" << endl;
}

Projectile::~Projectile() {
    cout << "Объект класса Projectile уничтожен" << endl;
}

void Projectile::update() {
    cout << "Метод update() класса Projectile выполнен" << endl;
}

bool Projectile::check_collision(Enemy* enemy) {
    cout << "Метод check_collision() класса Projectile выполнен" << endl;
    return false;
}

void Projectile::on_hit() {
    cout << "Метод on_hit() класса Projectile выполнен" << endl;
    is_active = false;
}

void Projectile::check_boundaries() {
    cout << "Метод check_boundaries() класса Projectile выполнен" << endl;
}

void Projectile::draw() {
    cout << "Метод draw() класса Projectile выполнен" << endl;
}