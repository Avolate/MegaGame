#include "HealthPotion.h"
#include <cstdlib>

HealthPotion::HealthPotion() : GameObject()
{
    x = 750.0f;
    y = static_cast<float>(rand() % 550);
    velocityX = -100.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
}

void HealthPotion::update(float deltaTime)
{
    x += velocityX * deltaTime;
    shape.setPosition(x, y);

    if (x < -50.0f)
        isActive = false;
}

void HealthPotion::draw(sf::RenderWindow& window)
{
    if (isActive)
        window.draw(shape);
}
