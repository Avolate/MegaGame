#include "BossBoulder.h"

BossBoulder::BossBoulder() : GameObject(), health(5)
{
    x = 750.0f;
    y = 250.0f;
    velocityX = -150.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(60.0f);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
}

void BossBoulder::update(float deltaTime)
{
    x += velocityX * deltaTime;
    shape.setPosition(x, y);

    if (x < -130.0f)
        isActive = false;
}

void BossBoulder::draw(sf::RenderWindow& window)
{
    if (isActive)
        window.draw(shape);
}
