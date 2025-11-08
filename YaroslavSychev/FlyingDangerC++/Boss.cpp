#include "Boss.hpp"
#include "GameManager.hpp"

Boss::Boss() : Enemy(), phase(1), size(10), damage(30) {
    cout << "Объект класса Boss создан" << endl;
}

Boss::Boss(int hp, int spd, int ph, int sz, int dmg) : Enemy(hp, spd), phase(ph), size(sz), damage(dmg) {
    cout << "Объект класса Boss создан с параметрами" << endl;
}

Boss::Boss(int hp, int spd, int ph, int sz, int dmg, GameManager* gm) : Enemy(hp, spd, gm), phase(ph), size(sz), damage(dmg) {
    cout << "Объект класса Boss создан с ссылкой на GameManager" << endl;
}

Boss::~Boss() {
    cout << "Объект класса Boss уничтожен" << endl;
}

void Boss::move() {
    cout << "Метод move() класса Boss выполнен" << endl;
    cout << "Босс фазы " << phase << " движется к цели" << endl;
}

void Boss::take_damage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Boss выполнен" << endl;
    cout << "Получено урона: " << amount << ", осталось здоровья: " << health << endl;

    if (health < max_health * 0.5 && phase == 1) {
        change_phase();
    }

    if (!isAlive()) {
        cout << "Босс побежден!" << endl;
    }
}

bool Boss::check_collision(const string& target) {
    cout << "Метод check_collision() класса Boss выполнен с целью: " << target << endl;
    return true;
}

void Boss::update() {
    cout << "Метод update() класса Boss выполнен" << endl;

    // Логика обновления босса
    move();

    // Специальные атаки в зависимости от фазы
    if (phase > 1) {
        cout << "Босс использует специальную атаку фазы " << phase << endl;
    }
}

void Boss::draw() {
    cout << "Метод draw() класса Boss выполнен" << endl;
    cout << "Отрисовка босса размера " << size << " в фазе " << phase << endl;
}

void Boss::apply_damage(int amount) {
    cout << "Метод apply_damage() класса Boss выполнен" << endl;
    take_damage(amount);
}

void Boss::change_phase() {
    phase++;
    cout << "Босс перешел в фазу " << phase << "!" << endl;
    cout << "Скорость и урон увеличены!" << endl;

    speed += 2;
    damage += 10;
}