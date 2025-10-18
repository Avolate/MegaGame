#include "Boss.hpp"
#include "GameManager.hpp"

int firstPhase = 1;
int defaultBossSize = 10;
int defaultBossDamage = 30;
int dopSpeed = 2;
int dopDamage = 10;

Boss::Boss() : Enemy(), phase(firstPhase), size(defaultBossSize), damage(defaultBossDamage) {
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

void Boss::Move() {
    cout << "Метод move() класса Boss выполнен" << endl;
    cout << "Босс фазы " << phase << " движется к цели" << endl;
}

void Boss::TakeDamage(int amount) {
    health -= amount;
    cout << "Метод take_damage() класса Boss выполнен" << endl;
    cout << "Получено урона: " << amount << ", осталось здоровья: " << health << endl;

    if (health < max_health * 0.5 && phase == 1) {
        ChangePhase();
    }

    if (!IsAlive()) {
        cout << "Босс побежден!" << endl;
    }
}

bool Boss::CheckCollision(const string& target) {
    cout << "Метод check_collision() класса Boss выполнен с целью: " << target << endl;
    return true;
}

void Boss::Update() {
    cout << "Метод update() класса Boss выполнен" << endl;

    // Логика обновления босса
    Move();

    // Специальные атаки в зависимости от фазы
    if (phase > firstPhase) {
        cout << "Босс использует специальную атаку фазы " << phase << endl;
    }
}

void Boss::Draw() {
    cout << "Метод draw() класса Boss выполнен" << endl;
    cout << "Отрисовка босса размера " << size << " в фазе " << phase << endl;
}

void Boss::ApplyDamage(int amount) {
    cout << "Метод apply_damage() класса Boss выполнен" << endl;
    TakeDamage(amount);
}

void Boss::ChangePhase() {
    phase++;
    cout << "Босс перешел в фазу " << phase << "!" << endl;
    cout << "Скорость и урон увеличены!" << endl;

    speed += dopSpeed;
    damage += dopDamage;
}