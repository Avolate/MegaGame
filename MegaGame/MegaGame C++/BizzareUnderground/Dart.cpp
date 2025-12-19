#include "Dart.h"

Dart::Dart(float x, float y, float directionX)
    : GameObject(x, y), velocity(0.0f, 0.0f), isActive(true)
{
    shape.setSize(sf::Vector2f(15.0f, 5.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(46, 139, 87));

    velocity = sf::Vector2f(600.0f * directionX, 0.0f);
}

void Dart::update(float deltaTime)
{
    if (!isActive)
        return;

    sf::Vector2f newPos = shape.getPosition();
    newPos.x += velocity.x * deltaTime;

    if (newPos.x < 0 || newPos.x > 1200)
    {
        isActive = false;
        return;
    }

    shape.setPosition(newPos);
}

void Dart::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(shape);
    }
}

bool Dart::getIsActive() const
{
    return isActive;
}

void Dart::destroy()
{
    isActive = false;
}
