#include "Archer.h"

Archer::Archer() : GameObject()
{
    x = 200.0f;
    y = 250.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setSize(sf::Vector2f(50.0f, 80.0f));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);
}

void Archer::update(float deltaTime)
{
    // TODO: управление мышью будет в v0.3
    // Пока просто отрисовываем на месте
    shape.setPosition(x, y);
}

void Archer::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
