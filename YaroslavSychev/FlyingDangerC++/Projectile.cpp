#include "Projectile.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

// Статические переменные
int Projectile::active_projectiles = 0;
const int Projectile::MAX_PROJECTILES = 5;

Projectile::Projectile() : position(""), direction(""), speed(10), damage(10),
rect(""), is_active(true), owner(nullptr) {
    active_projectiles++;
    cout << "Объект класса Projectile создан. Активных снарядов: " << active_projectiles << endl;
}

Projectile::Projectile(const string& pos, const string& dir, int dmg)
    : position(pos), direction(dir), speed(10), damage(dmg), rect(""),
    is_active(true), owner(nullptr) {
    active_projectiles++;
    cout << "Объект класса Projectile создан с параметрами. Активных снарядов: " << active_projectiles << endl;
}

Projectile::Projectile(const string& pos, const string& dir, int dmg, Player* player)
    : position(pos), direction(dir), speed(10), damage(dmg), rect(""),
    is_active(true), owner(player) {
    active_projectiles++;
    cout << "Объект класса Projectile создан с владельцем. Активных снарядов: " << active_projectiles << endl;
}

Projectile::Projectile(const Projectile& other) :
    position(other.position), direction(other.direction), speed(other.speed),
    damage(other.damage), rect(other.rect), is_active(other.is_active),
    owner(other.owner) {
    if (is_active) {
        active_projectiles++;
    }
    cout << "Конструктор копирования Projectile выполнен. Активных снарядов: " << active_projectiles << endl;
}

Projectile::~Projectile() {
    if (is_active) {
        active_projectiles--;
    }
    cout << "Объект класса Projectile уничтожен. Активных снарядов: " << active_projectiles << endl;
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
    if (is_active) {
        active_projectiles--;
    }
    is_active = false;
}

void Projectile::CheckBoundaries() {
    cout << "Метод check_boundaries() класса Projectile выполнен" << endl;
}

void Projectile::Draw() {
    cout << "Метод draw() класса Projectile выполнен" << endl;
}

// Перегрузка оператора == для проверки лимита снарядов
bool Projectile::operator==(const Projectile& other) const {
    bool can_create = (active_projectiles < MAX_PROJECTILES);
    cout << "Проверка лимита снарядов: " << active_projectiles << "/" << MAX_PROJECTILES
        << " - " << (can_create ? "можно создать" : "ЛИМИТ ПРЕВЫШЕН") << endl;
    return can_create;
}