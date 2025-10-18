#include "Castle.hpp"

int currentHealth = 100;
int maxHealth = 100;

Castle::Castle() : health(currentHealth), max_health(maxHealth), position(""), sprite(""), rect("") {
    cout << "Объект класса Castle создан" << endl;
}

Castle::Castle(int max_hp) : health(max_hp), max_health(max_hp), position(""), sprite(""), rect("") {
    cout << "Объект класса Castle создан с максимальным здоровьем: " << max_hp << endl;
}

Castle::~Castle() {
    cout << "Объект класса Castle уничтожен" << endl;
}

void Castle::TakeDamage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Castle выполнен. Получено урона: " << amount << endl;
    cout << "Осталось здоровья замка: " << health << "/" << max_health << endl;
}

bool Castle::IsDestroyed() {
    bool destroyed = health <= 0;
    cout << "Метод is_destroyed() класса Castle выполнен. Результат: " << (destroyed ? "разрушен" : "цел") << endl;
    return destroyed;
}

void Castle::Draw() {
    cout << "Метод draw() класса Castle выполнен" << endl;
}