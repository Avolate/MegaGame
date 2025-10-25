#include "Heart.h"
#include <iostream>
#include <cstdlib>
#include <string>
Heart::Heart(int x, int y,   std::string sprite_path, int spd, int num, bool p_touch, bool f_touch):
    FallingObject(x, y, sprite_path, spd, num, p_touch, f_touch) {
    std::cout << "Объект Heart создан" << std::endl;
}
Heart::~Heart() {
    std::cout << "Объект Heart уничтожен" << std::endl;
}
void Heart::playerCatchHeart(int playerX, int playerY) {
    if (abs(abs(getpositionX() - playerX) < 10 && abs(getpositionY() - playerY) < 10) < 10) {
        setplayer_touch (true);
        std::cout << "Heart пойман игроком!" << std::endl;
    }
}

void Heart::plusHealth(int &health) {
    health+=1;
    std::cout << "Здоровье увеличено. Текущее здоровье: " << health << std::endl;

}