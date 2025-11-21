#include "Meteor.hpp"
#include "GameManager.hpp"

int defaultSize = 3;
int defaultMeteorDamage = 15;

Meteor::Meteor() : Enemy(), size(defaultSize), damage(defaultMeteorDamage) {
    cout << "Объект класса Meteor создан" << endl;
}

Meteor::Meteor(int hp, int spd, int sz, int dmg) : Enemy(hp, spd), size(sz), damage(dmg) {
    cout << "Объект класса Meteor создан с параметрами" << endl;
}

Meteor::Meteor(int hp, int spd, int sz, int dmg, GameManager* gm) : Enemy(hp, spd, gm), size(sz), damage(dmg) {
    cout << "Объект класса Meteor создан с ссылкой на GameManager" << endl;
}

Meteor::Meteor(const Meteor& other) : Enemy(other), size(other.size), damage(other.damage) {
    cout << "Конструктор копирования Meteor выполнен" << endl;
}

Meteor::~Meteor() {
    cout << "Объект класса Meteor уничтожен" << endl;
}

void Meteor::Move() {
    cout << "Метод move() класса Meteor выполнен" << endl;
    cout << "Метеор размера " << size << " движется со скоростью " << speed << endl;
}

void Meteor::TakeDamage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Meteor выполнен" << endl;
    cout << "Получено урона: " << amount << ", осталось здоровья: " << health << endl;

    if (!IsAlive()) {
        cout << "Метеор уничтожен!" << endl;
    }
}

bool Meteor::CheckCollision(const string& target) {
    cout << "Метод check_collision() класса Meteor выполнен с целью: " << target << endl;
    return true;
}

void Meteor::Update() {
    cout << "Метод update() класса Meteor выполнен" << endl;

    // Логика обновления метеора
    Move();
    check_boundaries();
}

void Meteor::Draw() {
    cout << "Метод draw() класса Meteor выполнен" << endl;
    cout << "Отрисовка метеора размера " << size << " в позиции " << position << endl;
}

void Meteor::apply_damage(int amount) {
    cout << "Метод apply_damage() класса Meteor выполнен" << endl;
    TakeDamage(amount);
}

void Meteor::check_boundaries() {
    cout << "Метод check_boundaries() класса Meteor выполнен" << endl;
    cout << "Проверка границ экрана для метеора в позиции " << position << endl;

    // Здесь могла бы быть реальная логика проверки границ
    if (position.find("out") != string::npos) {
        cout << "Метеор вышел за границы экрана!" << endl;
    }
}