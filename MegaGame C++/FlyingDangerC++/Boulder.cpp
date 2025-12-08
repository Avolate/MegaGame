#include "Boulder.h"
#include <stdlib.h>
#include <time.h>

Boulder::Boulder() : GameObject()
{
    x = 750.0f;
    y = static_cast<float>(rand() % 550);
    velocityX = -150.0f - (rand() % 100);
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(30.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Boulder::update(float deltaTime)
{
    // TODO: реализовать логику движения
    x += velocityX * deltaTime;
    shape.setPosition(x, y);
}

void Boulder::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
