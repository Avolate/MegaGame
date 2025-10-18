#include "GameManager.hpp"
#include "Castle.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

GameManager::GameManager() : screen(""), clock(""), game_state("menu"), score(0), castle_health(100),
castle(nullptr), player(nullptr) {
    cout << "Объект класса GameManager создан" << endl;

    // Создание объектов, которыми управляет GameManager (композиция)
    castle = new Castle(100);
    player = new Player();
}

GameManager::~GameManager() {
    cout << "Объект класса GameManager уничтожен" << endl;

    // Очистка композиционных объектов
    delete castle;
    delete player;

    // Очистка агрегированных врагов
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

void GameManager::Run() {
    cout << "Метод run() класса GameManager запущен" << endl;
}

void GameManager::SwitchState() {
    cout << "Метод switch_state() класса GameManager выполнен" << endl;
}

void GameManager::CheckWinConditions() {
    cout << "Метод check_win_conditions() класса GameManager выполнен" << endl;
}

void GameManager::HandleEvents() {
    cout << "Метод handle_events() класса GameManager выполнен" << endl;
}

void GameManager::AddEnemy(Enemy* enemy) {
    enemies.push_back(enemy);
    cout << "Враг добавлен в GameManager" << endl;
}

void GameManager::RemoveEnemy(Enemy* enemy) {
    // Поиск и удаление врага из вектора
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (*it == enemy) {
            enemies.erase(it);
            cout << "Враг удален из GameManager" << endl;
            break;
        }
    }
}