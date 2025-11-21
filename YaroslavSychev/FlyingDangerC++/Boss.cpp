#include "Boss.hpp"
#include "GameManager.hpp"

int firstPhase = 1;
int currentPhase = 1;
int defaultBossSize = 10;
int defaultBossDamage = 30;
int dopSpeed = 2;
int dopDamage = 10;
float healthKoef = 0.5;

Boss::Boss() : Enemy(), phase(currentPhase), size(defaultBossSize), damage(defaultBossDamage) {
    cout << "Объект класса Boss создан" << endl;
}

Boss::Boss(int hp, int spd, int ph, int sz, int dmg) : Enemy(hp, spd), phase(ph), size(sz), damage(dmg) {
    cout << "Объект класса Boss создан с параметрами" << endl;
}

Boss::Boss(int hp, int spd, int ph, int sz, int dmg, GameManager* gm) : Enemy(hp, spd, gm), phase(ph), size(sz), damage(dmg) {
    cout << "Объект класса Boss создан с ссылкой на GameManager" << endl;
}

Boss::Boss(const Boss& other) : Enemy(other), phase(other.phase), size(other.size), damage(other.damage) {
    cout << "Конструктор копирования Boss выполнен" << endl;
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

    if (health < max_health * healthKoef && phase == firstPhase) {
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

// Перегрузка оператора << для уменьшения размера при получении урона
ostream& operator<<(ostream& os, Boss& boss) {
    // Уменьшаем размер босса при выводе (симуляция получения урона)
    if (boss.size > 3) {
        boss.size--;
        cout << "Босс уменьшился в размере после получения урона! Новый размер: " << boss.size << endl;
    }

    os << "Boss: Phase=" << boss.phase << ", Size=" << boss.size
        << ", Damage=" << boss.damage << ", Health=" << boss.health;
    return os;
}

// Дружественная функция для анализа босса
void AnalyzeBoss(const Boss& boss) {
    cout << "\n=== АНАЛИЗ БОССА ===" << endl;
    cout << "Фаза: " << boss.phase << endl;
    cout << "Размер: " << boss.size << endl;
    cout << "Урон: " << boss.damage << endl;
    cout << "Здоровье: " << boss.health << "/" << boss.max_health << endl;
    cout << "Скорость: " << boss.speed << endl;

    if (boss.phase > 1) {
        cout << "Босс в усиленной фазе! Будьте осторожны!" << endl;
    }
    cout << "=====================" << endl;
}