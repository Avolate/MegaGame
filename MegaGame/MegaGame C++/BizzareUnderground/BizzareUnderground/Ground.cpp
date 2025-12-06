#include "Ground.h"

Ground::Ground(float x, float y, float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Ground::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Ground::getBounds() const
{
    return shape.getGlobalBounds();
}