#include "HealthPotion.h"
#include <stdlib.h>

HealthPotion::HealthPotion() : GameObject()
{
    x = 750.0f;
    y = static_cast<float>(rand() % 550);
    velocityX = -100.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
}

void HealthPotion::update(float deltaTime)
{
    // TODO: реализовать логику движения
    x += velocityX * deltaTime;
    shape.setPosition(x, y);
}

void HealthPotion::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
