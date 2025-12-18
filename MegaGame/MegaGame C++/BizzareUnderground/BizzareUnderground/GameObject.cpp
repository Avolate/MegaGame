#include "GameObject.h"

GameObject::GameObject(float startX, float startY)
    : x(startX), y(startY)
{
}

sf::FloatRect GameObject::getBounds() const
{
    return shape.getGlobalBounds();
}

void GameObject::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
    shape.setPosition(x, y);
}

sf::Vector2f GameObject::getPosition() const
{
    return sf::Vector2f(x, y);
}

sf::RectangleShape& GameObject::getShape()
{
    return shape;
}
