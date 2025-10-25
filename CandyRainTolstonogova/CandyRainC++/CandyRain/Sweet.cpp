#include "Sweet.h"
#include <iostream> // For cout
#include <cstdlib> // For abs()
#include <string>

Sweet::Sweet(int x, int y,  std::string sprite_path, int spd, int num, bool p_touch, bool f_touch) :
    FallingObject(x, y, sprite_path, spd, num, p_touch, f_touch) {
    std::cout << "ќбъект Sweet создан" << std::endl;
}
Sweet::~Sweet() {
    std::cout << "ќбъект Sweet уничтожен" << std::endl;
}
void Sweet::playerCatchSweet(int playerX, int playerY){
    if (abs(getpositionX() - playerX) < 10 && abs(getpositionY() - playerY) < 10) {
        setplayer_touch (true) ;
        std::cout << "Sweet пойман игроком!" << std::endl;
    }
}

void Sweet::sweetTouchFloor() {
    if (getpositionY() <= GameMain::floorY) {
        setfloor_touch (true);
        std::cout << "Sweet коснулс€ пола" << std::endl;
    }
} 
void Sweet::changeCandy(int& count_candy) {
    count_candy-=1;
    std::cout << "—четчик конфет уменьшен: " << count_candy << std::endl;
}

void Sweet::changeCake(int& count_cake) {
    count_cake-=1;
    std::cout << "—четчик тортов уменьшен: " << count_cake << std::endl;
}

void Sweet::changeDonut(int& count_donut) {
    count_donut-=1;
    std::cout << "—четчик пончиков уменьшен: " << count_donut << std::endl;
}

