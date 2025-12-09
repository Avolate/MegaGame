#include "Projectile.h"

Projectile::Projectile(float startX, float startY) : GameObject()
{
    x = startX;
    y = startY;
    velocityX = 400.0f;
    velocityY = 0.0f;
    isActive = true;

    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
}

void Projectile::update(float deltaTime)
{
    x += velocityX * deltaTime;
    shape.setPosition(x, y);

    if (x > 850.0f)
        isActive = false;
}

void Projectile::draw(sf::RenderWindow& window)
{
    if (isActive)
        window.draw(shape);
}
