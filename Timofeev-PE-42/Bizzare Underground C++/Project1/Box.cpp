#include "Box.h"
#include <iostream>

Box::Box() : isHanged(false), speedFalling(2), speedMovement(3) {
    std::cout << "--- Box Initialized ---" << std::endl;
    std::cout << "  Is Hanged: " << std::boolalpha << getIsHanged() << std::endl;
    std::cout << "  Speed Falling: " << getSpeedFalling() << std::endl;
    std::cout << "  Speed Movement: " << getSpeedMovement() << std::endl;
}

Box::~Box() {
    std::cout << "--- Box Destroyed ---" << std::endl;
}

void Box::checkHanged() {
    std::cout << "Box::checkHanged() called. Checking if box is hanging." << std::endl;
}

void Box::fallingBox() {
    std::cout << "Box::fallingBox() called. Simulating fall." << std::endl;
    std::cout << "Box::fallingBox(): Box is falling. (Requires GameObject positionY)" << std::endl;
}

void Box::movementBox() {
    std::cout << "Box::movementBox() called. Simulating movement." << std::endl;
}

bool Box::characterBoxContact(int characterPositionX, int characterPositionY) {
    std::cout << "Box::characterBoxContact() called. Checking Character(" << characterPositionX << ", " << characterPositionY << ") against Box." << std::endl;
    return false;
}

bool Box::getIsHanged() const { return isHanged; }
int Box::getSpeedFalling() const { return speedFalling; }
int Box::getSpeedMovement() const { return speedMovement; }

void Box::setIsHanged(bool hanged) {
    isHanged = hanged;
    std::cout << "Box::setIsHanged() called. New state: isHanged = " << std::boolalpha << isHanged << std::endl;
}
void Box::setSpeedFalling(int sf) {
    speedFalling = sf;
    std::cout << "Box::setSpeedFalling() called. New speed: " << speedFalling << std::endl;
}
void Box::setSpeedMovement(int sm) {
    speedMovement = sm;
    std::cout << "Box::setSpeedMovement() called. New speed: " << speedMovement << std::endl;
}