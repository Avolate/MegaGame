#include "Projectile.h"

Projectile::Projectile(float startX, float startY) : GameObject()
{
	x = startX;
	y = startY;
	velocityX = 800.0f;
	velocityY = 0.0f;
	isActive = true;

	// Загружаем спрайт пули (laserred 24x7)
	if (!texture.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\FlyingDangerC++\\assets/laserred.png"))
	{
		// Fallback
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Projectile::update(float deltaTime)
{
	x += velocityX * deltaTime;
	sprite.setPosition(x, y);

	if (x > 1600.0f)
		isActive = false;
}

void Projectile::draw(sf::RenderWindow& window)
{
	if (isActive)
		window.draw(sprite);
}
