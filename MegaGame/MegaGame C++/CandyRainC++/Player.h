#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed;
    int health;
    int maxHealth;

public:
    Player(float x, float y, float spd, int maxHp, sf::Texture& playerTex);
    ~Player();

    void update(float deltaTime, int windowWidth);
    void draw(sf::RenderWindow& window);
    void moveLeft();
    void moveRight();
    void takeDamage(int damage);
    void heal(int amount);

    sf::FloatRect getBounds() const;
    int getHealth() const;
    int getMaxHealth() const;
    void setPosition(float x, float y);
};
