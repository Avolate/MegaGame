#include "GameObject.h"
#include <iostream>
GameObject::GameObject(int x, int y,  const std::string &spritepath) :
    positionX(x), positionY(y), sprite(spritepath) {
    std::cout << "Объект GameObject создан" << std::endl;
}

GameObject::~GameObject() {
    std::cout << "Объект GameObject уничтожен" << std::endl;
}
// Getter
int GameObject::GetpositionX() const { return positionX; }
int GameObject::GetpositionY() const { return positionY; }
std::string GameObject::Getsprite() const { return sprite; }

// Setter
void GameObject::SetpositionX(int count) { positionX = count; }
void GameObject::SetpositionY(int count) { positionY = count; }
void GameObject::Setsprite(std::string bg) { sprite = bg; }

void GameObject::DisplayInfo() const {
    std::cout << "GameObject: X=" << positionX << ", Y=" << positionY
        << ", Sprite=" << sprite << std::endl;
}