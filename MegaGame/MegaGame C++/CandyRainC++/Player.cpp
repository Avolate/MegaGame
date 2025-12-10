#include "Player.h"

Player::Player(float x, float y, float spd, int maxHp, sf::Texture& playerTex)
    : position(x, y), speed(spd), health(maxHp), maxHealth(maxHp) {
    sprite.setTexture(playerTex);
    sprite.setScale(0.308f, 0.305f);  // 100×160 (было 80×128)
    sprite.setPosition(position);
}

Player::~Player() {
}

void Player::update(float deltaTime, int windowWidth) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += speed * deltaTime;
    }

    float playerWidth = sprite.getGlobalBounds().width;
    if (position.x < 0) position.x = 0;
    if (position.x + playerWidth > windowWidth) position.x = windowWidth - playerWidth;

    sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::moveLeft() {
    position.x -= speed * 0.016f;
}

void Player::moveRight() {
    position.x += speed * 0.016f;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    sprite.setPosition(position);
}
