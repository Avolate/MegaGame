#include "FallingObject.h"

FallingObject::FallingObject(float x, float y, float vel)
    : position(x, y), velocity(vel), isActive(true) {
}

FallingObject::~FallingObject() {
}

void FallingObject::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
}

sf::Vector2f FallingObject::getPosition() const {
    return position;
}

bool FallingObject::getActive() const {
    return isActive;
}

void FallingObject::setActive(bool active) {
    isActive = active;
}
