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

void Projectile::Update() {
    cout << "Метод update() класса Projectile выполнен" << endl;
}

bool Projectile::CheckCollision(Enemy* enemy) {
    cout << "Метод check_collision() класса Projectile выполнен" << endl;
    return false;
}

void Projectile::OnHit() {
    cout << "Метод on_hit() класса Projectile выполнен" << endl;
    is_active = false;
}

void Projectile::CheckBoundaries() {
    cout << "Метод check_boundaries() класса Projectile выполнен" << endl;
}

void Projectile::Draw() {
    cout << "Метод draw() класса Projectile выполнен" << endl;
}