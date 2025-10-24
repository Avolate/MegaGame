#include "Character.h"
#include <iostream>

Character::Character() : isAlive(true), speedCharacter(5), isHanged(false) {
    // ”станавливаем позицию, использу€ сеттер
    setPositionX(10);
    setPositionY(10);
    // ”станавливаем спрайт, использу€ сеттер
    setSprite("player_sprite.png");
    std::cout << "--- Character Initialized ---" << std::endl;
    std::cout << "  Position: (" << getPositionX() << ", " << getPositionY() << ")" << std::endl;
    std::cout << "  Sprite: '" << getSprite() << "'" << std::endl;
    std::cout << "  Is Alive: " << std::boolalpha << getIsAlive() << std::endl;
    std::cout << "  Speed: " << getSpeedCharacter() << std::endl;
    std::cout << "  Is Hanged: " << std::boolalpha << getIsHanged() << std::endl;
}

Character::~Character() {
    std::cout << "--- Character Destroyed ---" << std::endl;
    std::cout << "  Final Position: (" << getPositionX() << ", " << getPositionY() << ")" << std::endl;
    std::cout << "  Final State: Alive = " << std::boolalpha << getIsAlive() << std::endl;
}

void Character::movementRight() {
    std::cout << "Character::movementRight() called. Current X: " << getPositionX() << std::endl;
    setPositionX(getPositionX() + getSpeedCharacter());
    std::cout << "Character::movementRight(): Moved Right. New position X: " << getPositionX() << std::endl;
}

void Character::movementLeft() {
    std::cout << "Character::movementLeft() called. Current X: " << getPositionX() << std::endl;
    setPositionX(getPositionX() - getSpeedCharacter());
    std::cout << "Character::movementLeft(): Moved Left. New position X: " << getPositionX() << std::endl;
}

void Character::jump() {
    std::cout << "Character::jump() called. Performing jump." << std::endl;
}

void Character::fallingCharacter() {
    std::cout << "Character::fallingCharacter() called. Current Y: " << getPositionY() << std::endl;
    setPositionY(getPositionY() - 1); // »митаци€ падени€ на 1 единицу
    std::cout << "Character::fallingCharacter(): Falling. New position Y: " << getPositionY() << std::endl;
}

// Getters
bool Character::getIsAlive() const { return isAlive; }
int Character::getSpeedCharacter() const { return speedCharacter; }
bool Character::getIsHanged() const { return isHanged; }

// Setters
void Character::setIsAlive(bool alive) {
    isAlive = alive;
    std::cout << "Character::setIsAlive() called. New state: isAlive = " << std::boolalpha << isAlive << std::endl;
}
void Character::setSpeedCharacter(int speed) {
    speedCharacter = speed;
    std::cout << "Character::setSpeedCharacter() called. New speed: " << speedCharacter << std::endl;
}
void Character::setIsHanged(bool hanged) {
    isHanged = hanged;
    std::cout << "Character::setIsHanged() called. New state: isHanged = " << std::boolalpha << isHanged << std::endl;
}