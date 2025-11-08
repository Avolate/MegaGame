#include "Key.h"
#include <iostream>

Key::Key() {
    std::cout << "--- Key created on the map ---" << std::endl;
}

Key::~Key() {
    std::cout << "--- Key destroyed. ---" << std::endl;
}

bool Key::characterKeyContact(int characterPositionX, int characterPositionY) {
    std::cout << "Key::characterKeyContact() called. Character at (" << characterPositionX << ", " << characterPositionY << ") found key." << std::endl;
    return true; // Предполагаем контакт для демонстрации
}

int Key::keyDestroy(int keyCounter) {
    std::cout << "Key::keyDestroy() called. Current key count: " << keyCounter << std::endl;
    int newCounter = keyCounter + 1;
    std::cout << "Key::keyDestroy(): Key picked up. New total keys: " << newCounter << std::endl;
    return newCounter;
}