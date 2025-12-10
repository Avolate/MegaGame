#include "BossBoulder.h"

BossBoulder::BossBoulder() : GameObject(), health(5)
{
	x = 1500.0f;
	y = 150.0f;
	velocityX = -200.0f;
	velocityY = 0.0f;
	isActive = true;

	// Загружаем спрайт босса (boss 500x500)
	if (!texture.loadFromFile("assets/boss.png"))
	{
		// Fallback
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void BossBoulder::update(float deltaTime)
{
	x += velocityX * deltaTime;
	sprite.setPosition(x, y);

	if (x < -600.0f)
		isActive = false;
}

void BossBoulder::draw(sf::RenderWindow& window)
{
	if (isActive)
		window.draw(sprite);
}
