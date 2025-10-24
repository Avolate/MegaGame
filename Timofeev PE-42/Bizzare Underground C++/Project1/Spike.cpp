#include "Spike.h"
#include <iostream>

Spike::Spike() : isHide(true) {
    std::cout << "Spike created. Initial state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

Spike::~Spike() {
    std::cout << "Spike destroyed. Final state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

bool Spike::characterSpikeContact(int characterPositionX, int characterPositionY) {
    std::cout << "Spike::characterSpikeContact() called. Checking Character(" << characterPositionX << ", " << characterPositionY << ") against Spike at (" << 0 << ", " << 0 << ")." << std::endl;
    // Имитация: если позиция совпадает и шип активен
    if (!getIsHide() && characterPositionX == 0 && characterPositionY == 0) {
        std::cout << "Spike::characterSpikeContact(): Contact!" << std::endl;
        return true;
    }
    std::cout << "Spike::characterSpikeContact(): No contact." << std::endl;
    return false;
}

void Spike::putingSpike() {
    std::cout << "Spike::putingSpike() called. Current isHide: " << std::boolalpha << getIsHide() << std::endl;
    setIsHide(false);
    std::cout << "Spike::putingSpike(): Spike extended (made active). New state: isHide = " << std::boolalpha << getIsHide() << std::endl;
}

bool Spike::getIsHide() const { return isHide; }
void Spike::setIsHide(bool hide) {
    isHide = hide;
    std::cout << "Spike::setIsHide() called. New state: isHide = " << std::boolalpha << isHide << std::endl;
}