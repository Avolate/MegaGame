#include "Door.h"
#include <iostream>

Door::Door() : keyCounter(0) {
    std::cout << "--- Door Initialized ---" << std::endl;
    std::cout << "  Required keys: 3" << std::endl;
}

Door::~Door() {
    std::cout << "--- Door Destroyed ---" << std::endl;
}

void Door::doorOpen() {
    std::cout << "Door::doorOpen() called. Current key count: " << getKeyCounter() << std::endl;
    if (getKeyCounter() >= max_keys) {
        std::cout << "Door::doorOpen(): Opened successfully! Key count (" << getKeyCounter() << ") is sufficient." << std::endl;
    }
    else {
        std::cout << "Door::doorOpen(): Blocked. Need " << (max_keys - getKeyCounter()) << " more keys." << std::endl;
    }
}

int Door::getKeyCounter() const { return keyCounter; }
void Door::setKeyCounter(int count) {
    keyCounter = count;
    std::cout << "Door::setKeyCounter() called. New count: " << keyCounter << std::endl;
}