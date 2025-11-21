#include "Player.hpp"
#include "Projectile.hpp"
#include "GameManager.hpp"
#include "Meteor.hpp"

Player::Player() : position(""), sprite(""), rect(""), speed(5), is_alive(true),
shoot_cooldown(0.5f), score(0), game_manager(nullptr) {
    cout << "Объект класса Player создан" << endl;
}

Player::Player(GameManager* gm) : position(""), sprite(""), rect(""), speed(5), is_alive(true),
shoot_cooldown(0.5f), score(0), game_manager(gm) {
    cout << "Объект класса Player создан с ссылкой на GameManager" << endl;
}

Player::Player(const Player& other) :
    position(other.position), sprite(other.sprite), rect(other.rect),
    speed(other.speed), is_alive(other.is_alive), shoot_cooldown(other.shoot_cooldown),
    score(other.score), game_manager(other.game_manager) {

    // Глубокая копия снарядов
    for (auto proj : other.projectiles) {
        projectiles.push_back(new Projectile(*proj));
    }
    cout << "Конструктор копирования Player выполнен" << endl;
}

Player::~Player() {
    cout << "Объект класса Player уничтожен" << endl;

    // Очистка снарядов (агрегация)
    for (auto projectile : projectiles) {
        delete projectile;
    }
    projectiles.clear();
}

void Player::Move(const string& mouse_pos) {
    cout << "Метод move() класса Player выполнен. Позиция мыши: " << mouse_pos << endl;
}

void Player::Shoot() {
    cout << "Метод shoot() класса Player выполнен" << endl;

    // Создание нового снаряда (агрегация)
    Projectile* newProjectile = new Projectile(position, "forward", 10);
    AddProjectile(newProjectile);
}

void Player::TakeDamage() {
    cout << "Метод take_damage() класса Player выполнен" << endl;
    is_alive = false;
}

void Player::Update() {
    cout << "Метод update() класса Player выполнен" << endl;

    // Обновление всех снарядов
    for (auto projectile : projectiles) {
        projectile->Update();
    }
}

void Player::Draw() {
    cout << "Метод draw() класса Player выполнен" << endl;
}

void Player::AddProjectile(Projectile* projectile) {
    projectiles.push_back(projectile);
    cout << "Снаряд добавлен игроку" << endl;
}

void Player::RemoveProjectile(Projectile* projectile) {
    for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
        if (*it == projectile) {
            projectiles.erase(it);
            cout << "Снаряд удален у игрока" << endl;
            break;
        }
    }
}

// Перегрузка оператора + для добавления очков при попадании по метеору
Player& Player::operator+(Meteor* meteor) {
    if (meteor && meteor->getSize() <= 3) {  // Маленький метеор (размер <= 3)
        score += 1;
        cout << "Попадание по маленькому метеору! +1 очко. Счет: " << score << endl;
    }
    return *this;
}

string Player::GetPlayerInfo() const {
    return "Игрок: счет=" + to_string(score) + ", снарядов=" + to_string(projectiles.size());
}