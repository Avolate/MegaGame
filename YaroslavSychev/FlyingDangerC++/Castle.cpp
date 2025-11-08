#include "Castle.hpp"

Castle::Castle() : health(100), max_health(100), position(""), sprite(""), rect("") {
    cout << "Объект класса Castle создан" << endl;
}

Castle::Castle(int max_hp) : health(max_hp), max_health(max_hp), position(""), sprite(""), rect("") {
    cout << "Объект класса Castle создан с максимальным здоровьем: " << max_hp << endl;
}

Castle::~Castle() {
    cout << "Объект класса Castle уничтожен" << endl;
}

void Castle::take_damage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Castle выполнен. Получено урона: " << amount << endl;
    cout << "Осталось здоровья замка: " << health << "/" << max_health << endl;
}

bool Castle::is_destroyed() {
    bool destroyed = health <= 0;
    cout << "Метод is_destroyed() класса Castle выполнен. Результат: " << (destroyed ? "разрушен" : "цел") << endl;
    return destroyed;
}

void Castle::draw() {
    cout << "Метод draw() класса Castle выполнен" << endl;
}