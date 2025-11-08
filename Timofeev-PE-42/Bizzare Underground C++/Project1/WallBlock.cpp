#include "WallBlock.h"
#include <iostream>

WallBlock::WallBlock() : isHide(true) {
    std::cout << "WallBlock created. Initial state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

WallBlock::~WallBlock() {
    std::cout << "WallBlock destroyed. Final state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

void WallBlock::putingWall() {
    std::cout << "WallBlock::putingWall() called. Current isHide: " << std::boolalpha << getIsHide() << std::endl;
    setIsHide(false); // Блок становится осязаемым
    std::cout << "WallBlock::putingWall(): Block extended (made tangible). New state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

bool WallBlock::getIsHide() const { return isHide; }
void WallBlock::setIsHide(bool hide) {
    isHide = hide;
    std::cout << "WallBlock::setIsHide() called. New state: isHide = " << std::boolalpha << isHide << std::endl;
}