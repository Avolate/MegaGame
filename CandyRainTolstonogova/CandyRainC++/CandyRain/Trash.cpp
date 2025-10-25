#include "Trash.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include "GameMain.h"
Trash::Trash(int x, int y, std::string spritepath, int spd, int num, bool ptouch, bool ftouch) :
    FallingObject(x, y, spritepath, spd, num, ptouch, ftouch) {
    std::cout << "Объект Trash создан" << std::endl;
}
Trash::~Trash() {
    std::cout << "Объект Trash уничтожен" << std::endl;
}
void Trash::PlayerCatchTrash(int playerX, int playerY) {
    if (abs(GetpositionX() - playerX) < GameMain::playersize && abs(GetpositionY() - playerY) < GameMain::playersize) {
        Setplayertouch(true);
        std::cout << "Trash пойман игроком!" << std::endl;
    }
}