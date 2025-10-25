#include "Sweet.h"
#include <iostream> // For cout
#include <cstdlib> // For abs()
#include <string>
#include "GameMain.h"
Sweet::Sweet(int x, int y,  std::string spritepath, int spd, int num, bool ptouch, bool ftouch) :
    FallingObject(x, y, spritepath, spd, num, ptouch, ftouch) {
    std::cout << "ќбъект Sweet создан" << std::endl;
}
Sweet::~Sweet() {
    std::cout << "ќбъект Sweet уничтожен" << std::endl;
}
void Sweet::PLayerCatchSweet(int playerX, int playerY){
    if (abs(GetpositionX() - playerX) < GameMain::playersize && abs(GetpositionY() - playerY) < GameMain::playersize) {
        Setplayertouch (true) ;
        std::cout << "Sweet пойман игроком!" << std::endl;
    }
}

void Sweet::SweetTouchFloor() {
    if (GetpositionY() <= GameMain::floorY) {
        Setfloortouch (true);
        std::cout << "Sweet коснулс€ пола" << std::endl;
    }
} 
void Sweet::ChangeCandy(int& countcandy) {
    countcandy-= GameMain::countchange;
    std::cout << "—четчик конфет уменьшен: " << countcandy << std::endl;
}

void Sweet::ChangeCake(int& countcake) {
    countcake-= GameMain::countchange;
    std::cout << "—четчик тортов уменьшен: " << countcake << std::endl;
}

void Sweet::ChangeDonut(int& countdonut) {
    countdonut-= GameMain::countchange;
    std::cout << "—четчик пончиков уменьшен: " << countdonut << std::endl;
}

