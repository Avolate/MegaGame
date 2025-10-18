#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

    void run();
    void switch_state();
    void check_win_conditions();
    void handle_events();

    // Методы для управления объектами
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    void update() {
        cout << "Метод update() класса GameManager выполнен" << endl;
        cout << "Обновление состояния всех игровых объектов..." << endl;
    }
};

#endif