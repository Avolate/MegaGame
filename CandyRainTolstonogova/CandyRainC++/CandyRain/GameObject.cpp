#include "GameObject.h"
#include <iostream>
GameObject::GameObject(int x, int y,  const std::string &sprite_path) :
    positionX(x), positionY(y), sprite(sprite_path) {
    std::cout << "Объект GameObject создан" << std::endl;
}

GameObject::~GameObject() {
    std::cout << "Объект GameObject уничтожен" << std::endl;
}
// Getter
int GameObject::getpositionX() const { return positionX; }
int GameObject::getpositionY() const { return positionY; }
std::string GameObject::getsprite() const { return sprite; }

// Setter
void GameObject::setpositionX(int count) { positionX = count; }
void GameObject::setpositionY(int count) { positionY = count; }
void GameObject::setsprite(std::string bg) { sprite = bg; }

void GameObject::displayInfo() const {
    std::cout << "GameObject: X=" << positionX << ", Y=" << positionY
        << ", Sprite=" << sprite << std::endl;
}