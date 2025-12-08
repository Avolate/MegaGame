#include "Projectile.h"

Projectile::Projectile(float startX, float startY) : GameObject()
{
    x = startX;
    y = startY;
    velocityX = 400.0f;  // Летит вправо
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
}

void Projectile::update(float deltaTime)
{
    // TODO: реализовать логику движения
    x += velocityX * deltaTime;
    shape.setPosition(x, y);
}

void Projectile::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
