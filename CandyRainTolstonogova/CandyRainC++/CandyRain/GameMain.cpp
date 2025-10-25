#include "GameMain.h"
#include <iostream> // For cout
#include "Player.h"
#include "Sweets_distribution.h"
#include "Trash.h"
GameMain::GameMain(int h, const std::string& bg, std::string status) :
    health(h), background(bg), gamestatus(status)
{
    std::cout << "Объект GameMain создан" << std::endl;
}
GameMain::~GameMain() {
    std::cout << "Объект GameMain уничтожен" << std::endl;
}

void GameMain::Start() {

    gamestatus = "playing";
    std::cout << "Метод start запущен.Game started!" << std::endl;

   }

void GameMain::ChangeStatus() {
    if (gamestatus == "playing") {
        gamestatus = "paused";
        std::cout << "Game paused." << std::endl;
    }
    else {
        gamestatus = "playing";
        std::cout << "Game resumed." << std::endl;
    }
}

bool GameMain::WinCheck(int countcandy, int countcake, int countdonut) {
    if (health > 0 && (countcandy ==0 && countcake ==0 && countdonut ==0)) {
        std::cout << " Игрок победил!" << std::endl;
        return true;
    }
    else
        return false;
}

bool GameMain::LoseCheck() {
    if (health <= 0) {
        std::cout << "Проверка проигрыша: Игрок проиграл!" << std::endl;
        return true;
    }
    else {
        std::cout << "Проверка проигрыша: Игрок еще жив" << std::endl;
        return false;
    }
}
void GameMain::DisplayInfo() const {
        std::cout << "GameMain: Health=" << health << ", Background=" << background
            << ", Status=" << gamestatus << std::endl;
}
