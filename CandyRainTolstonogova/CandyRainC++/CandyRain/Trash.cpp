#include "Trash.h"
#include <iostream>
#include <cstdlib>
#include <string>
Trash::Trash(int x, int y, std::string sprite_path, int spd, int num, bool p_touch, bool f_touch) :
    FallingObject(x, y, sprite_path, spd, num, p_touch, f_touch) {
    std::cout << "Объект Trash создан" << std::endl;
}
Trash::~Trash() {
    std::cout << "Объект Trash уничтожен" << std::endl;
}
void Trash::playerCatchTrash(int playerX, int playerY) {
    if (abs(getpositionX() - playerX) < 5 && abs(getpositionY() - playerY) < 5) {
        setplayer_touch(true);
        std::cout << "Trash пойман игроком!" << std::endl;
    }
}