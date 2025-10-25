#include "Heart.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "GameMain.h"
Heart::Heart(int x, int y,   std::string spritepath, int spd, int num, bool ptouch, bool ftouch):
    FallingObject(x, y, spritepath, spd, num, ptouch, ftouch) {
    std::cout << "Объект Heart создан" << std::endl;
}
Heart::~Heart() {
    std::cout << "Объект Heart уничтожен" << std::endl;
}
void Heart::PlayerCatchHeart(int playerX, int playerY) {
    if (abs(GetpositionX() - playerX) < GameMain::playersize && abs(GetpositionY() - playerY) < GameMain::playersize) {
        Setplayertouch (true);
        std::cout << "Heart пойман игроком!" << std::endl;
    }
}

void Heart::PlusHealth(int &health) {
    health+=1;
    std::cout << "Здоровье увеличено. Текущее здоровье: " << health << std::endl;

}