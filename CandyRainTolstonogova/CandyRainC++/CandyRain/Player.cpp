#include "Player.h"
#include <iostream> 
#include "GameObject.h"

Player::Player(int x, int y, const std::string& spritepath, int spd, bool alive) :
    GameObject(x, y, spritepath), speed(spd), life(alive) {
    std::cout << "Объект Player создан" << std::endl;
}

Player::~Player() {
    std::cout << "Объект Player уничтожен" << std::endl;
}
void Player::MoveRight() {
    int newposition = GetpositionX();
    newposition += speed;
    SetpositionX(newposition);
    std::cout << "Player перемещен вправо. Новая позиция X: " << GetpositionX() << std::endl; 
}

void Player::MoveLeft() {
    int newposition = GetpositionX();
    newposition -= speed;
    SetpositionX(newposition);
    std::cout << "Player перемещен влево. Новая позиция X: " << GetpositionX() << std::endl;
}

// Getter
int Player::GetLife() const { return life; }

// Setter
void Player::SetLife(int count) {life = count; }
