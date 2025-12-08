#include "GameObject.h"

void GameObject::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

sf::Vector2f GameObject::getPosition() const
{
    return sf::Vector2f(x, y);
}
