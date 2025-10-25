#include "Player.h"
#include <iostream> 
#include "GameObject.h"

Player::Player(int x, int y, const std::string& sprite_path, int spd, bool alive) :
    GameObject(x, y, sprite_path), speed(spd), life(alive) {
    std::cout << "Объект Player создан" << std::endl;
}

Player::~Player() {
    std::cout << "Объект Player уничтожен" << std::endl;
}
void Player::moveRight() {
    int new_position = getpositionX();
    new_position += speed;
    setpositionX(new_position);
    std::cout << "Player перемещен вправо. Новая позиция X: " << getpositionX() << std::endl; 
}

void Player::moveLeft() {
    int new_position = getpositionX();
    new_position -= speed;
    setpositionX(new_position);
    std::cout << "Player перемещен влево. Новая позиция X: " << getpositionX() << std::endl;
}

// Getter
int Player::getlife() const { return life; }

// Setter
void Player::setlife(int count) {life = count; }
