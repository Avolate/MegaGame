#include "Button.h"
#include <iostream>

Button::Button() : isPressed(false), cooldownButton(100) {
    std::cout << "--- Button Initialized ---" << std::endl;
    std::cout << "  Cooldown: " << getCooldownButton() << std::endl;
}

Button::~Button() {
    std::cout << "--- Button Destroyed ---" << std::endl;
}

bool Button::characterButtonContact(int characterPositionX, int characterPositionY) {
    std::cout << "Button::characterButtonContact() called. Character at (" << characterPositionX << ", " << characterPositionY << ") pressed button." << std::endl;
    setIsPressed(true);
    return true;
}

bool Button::boxButtonContact(int boxPositionX, int boxPositionY) {
    std::cout << "Button::boxButtonContact() called. Box at (" << boxPositionX << ", " << boxPositionY << ") pressed button." << std::endl;
    setIsPressed(true);
    return true;
}

bool Button::buttonChanges(bool wallBlockIsHide, bool spikeIsHide) {
    std::cout << "Button::buttonChanges() called. Applying changes." << std::endl;
    std::cout << "WallBlock hide status set to: " << std::boolalpha << wallBlockIsHide << std::endl;
    std::cout << "Spike hide status set to: " << std::boolalpha << spikeIsHide << std::endl;
    return true;
}

bool Button::getIsPressed() const { return isPressed; }
int Button::getCooldownButton() const { return cooldownButton; }

void Button::setIsPressed(bool pressed) {
    isPressed = pressed;
    std::cout << "Button::setIsPressed() called. New state: isPressed = " << std::boolalpha << isPressed << std::endl;
}
void Button::setCooldownButton(int cooldown) {
    cooldownButton = cooldown;
    std::cout << "Button::setCooldownButton() called. New cooldown: " << cooldownButton << std::endl;
}