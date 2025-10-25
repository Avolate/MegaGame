#include "GameObject.h"
#include <iostream>

// Базовый класс GameObject
GameObject::GameObject() : positionX(0), positionY(0), sprite("") {
    std::cout << "GameObject (Base) created." << std::endl; 
}

GameObject::~GameObject() {
    std::cout << "GameObject (Base) destroyed." << std::endl;
}

// Getters
int GameObject::getPositionX() const { return positionX; }
int GameObject::getPositionY() const { return positionY; }
std::string GameObject::getSprite() const { return sprite; }

// Setters
void GameObject::setPositionX(int x) {
    std::cout << "GameObject: Setting positionX to " << x << "." << std::endl;
    positionX = x;
}
void GameObject::setPositionY(int y) {
    std::cout << "GameObject: Setting positionY to " << y << "." << std::endl;
    positionY = y;
}
void GameObject::setSprite(const std::string& s) {
    std::cout << "GameObject: Setting sprite to '" << s << "'." << std::endl;
    sprite = s;
}