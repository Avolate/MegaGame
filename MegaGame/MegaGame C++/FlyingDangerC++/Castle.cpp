#include "Castle.h"

Castle::Castle() : GameObject(), health(3)
{
    x = 0.0f;
    y = 0.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setSize(sf::Vector2f(100.0f, 600.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void Castle::update(float deltaTime)
{
    // Замок статичен
}

void Castle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
