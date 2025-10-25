#include "GameMain.h"
#include <iostream> // For cout
#include "Player.h"
#include "Sweets_distribution.h"
#include "Trash.h"
GameMain::GameMain(int h, const std::string& bg, std::string status) :
    health(h), background(bg), game_status(status)
{
    std::cout << "Объект GameMain создан" << std::endl;
}
GameMain::~GameMain() {
    std::cout << "Объект GameMain уничтожен" << std::endl;
}

void GameMain::start() {

    game_status = "playing";
    std::cout << "Метод start запущен.Game started!" << std::endl;

   }

void GameMain::changeStatus() {
    if (game_status == "playing") {
        game_status = "paused";
        std::cout << "Game paused." << std::endl;
    }
    else {
        game_status = "playing";
        std::cout << "Game resumed." << std::endl;
    }
}

bool GameMain::winCheck(int count_candy, int count_cake, int count_donut) {
    if (health > 0 && (count_candy ==0 && count_cake ==0 && count_donut ==0)) {
        std::cout << " Игрок победил!" << std::endl;
        return true;
    }
    else
        return false;
}

bool GameMain::loseCheck() {
    if (health <= 0) {
        std::cout << "Проверка проигрыша: Игрок проиграл!" << std::endl;
        return true;
    }
    else {
        std::cout << "Проверка проигрыша: Игрок еще жив" << std::endl;
        return false;
    }
}
void GameMain::displayInfo() const {
        std::cout << "GameMain: Health=" << health << ", Background=" << background
            << ", Status=" << game_status << std::endl;
}
