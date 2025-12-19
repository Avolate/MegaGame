#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
protected:
    float x, y;
    sf::RectangleShape shape;

public:
    GameObject(float startX, float startY);
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const;

    virtual void setPosition(float newX, float newY);
    sf::Vector2f getPosition() const;

    sf::RectangleShape& getShape();
};
