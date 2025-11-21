#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Предварительные объявления
class Castle;
class Player;
class Enemy;

class GameManager {
private:
    string screen;
    string clock;
    string game_state;
    int score;
    int castle_health;

    // Композиция: GameManager владеет этими объектами
    Castle* castle;
    Player* player;
    vector<Enemy*> enemies;

public:
    GameManager();
    ~GameManager();

    void Run();
    void SwitchState();
    void CheckWinConditions();
    void HandleEvents();

    // Методы для управления объектами
    void AddEnemy(Enemy* enemy);
    void RemoveEnemy(Enemy* enemy);

    // Встроенная реализация Update
    void Update() {
        cout << "Метод update() класса GameManager выполнен" << endl;
        cout << "Обновление состояния всех игровых объектов..." << endl;
    }
};