#include "Boulder.h"
#include <cstdlib>

Boulder::Boulder() : GameObject()
{
    x = 750.0f;
    y = static_cast<float>(rand() % 550);
    velocityX = -150.0f - (rand() % 100);  // -150 до -250
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(30.0f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void Boulder::update(float deltaTime)
{
    x += velocityX * deltaTime;
    shape.setPosition(x, y);

    // Удаляем, если вышёл за экран влево
    if (x < -50.0f)
        isActive = false;
}

void Boulder::draw(sf::RenderWindow& window)
{
    if (isActive)
        window.draw(shape);
}
