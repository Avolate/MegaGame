#include "Meteor.hpp"
#include "GameManager.hpp"

Meteor::Meteor() : Enemy(), size(3), damage(15) {
    cout << "Объект класса Meteor создан" << endl;
}

Meteor::Meteor(int hp, int spd, int sz, int dmg) : Enemy(hp, spd), size(sz), damage(dmg) {
    cout << "Объект класса Meteor создан с параметрами" << endl;
}

Meteor::Meteor(int hp, int spd, int sz, int dmg, GameManager* gm) : Enemy(hp, spd, gm), size(sz), damage(dmg) {
    cout << "Объект класса Meteor создан с ссылкой на GameManager" << endl;
}

Meteor::~Meteor() {
    cout << "Объект класса Meteor уничтожен" << endl;
}

void Meteor::move() {
    cout << "Метод move() класса Meteor выполнен" << endl;
    cout << "Метеор размера " << size << " движется со скоростью " << speed << endl;
}

void Meteor::take_damage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Meteor выполнен" << endl;
    cout << "Получено урона: " << amount << ", осталось здоровья: " << health << endl;

    if (!isAlive()) {
        cout << "Метеор уничтожен!" << endl;
    }
}

bool Meteor::check_collision(const string& target) {
    cout << "Метод check_collision() класса Meteor выполнен с целью: " << target << endl;
    return true;
}

void Meteor::update() {
    cout << "Метод update() класса Meteor выполнен" << endl;

    // Логика обновления метеора
    move();
    check_boundaries();
}

void Meteor::draw() {
    cout << "Метод draw() класса Meteor выполнен" << endl;
    cout << "Отрисовка метеора размера " << size << " в позиции " << position << endl;
}

void Meteor::apply_damage(int amount) {
    cout << "Метод apply_damage() класса Meteor выполнен" << endl;
    take_damage(amount);
}

void Meteor::check_boundaries() {
    cout << "Метод check_boundaries() класса Meteor выполнен" << endl;
    cout << "Проверка границ экрана для метеора в позиции " << position << endl;

    // Здесь могла бы быть реальная логика проверки границ
    if (position.find("out") != string::npos) {
        cout << "Метеор вышел за границы экрана!" << endl;
    }
}