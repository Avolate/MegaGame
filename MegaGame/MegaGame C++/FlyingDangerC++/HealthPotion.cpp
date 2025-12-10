#include "HealthPotion.h"
#include <cstdlib>

HealthPotion::HealthPotion() : GameObject()
{
	x = 1500.0f;
	y = static_cast<float>(rand() % (800 - 64));
	velocityX = -150.0f;
	velocityY = 0.0f;
	isActive = true;

	// «агружаем спрайт здоровь€ (stone3, используем stone)
	if (!texture.loadFromFile("assets/stone.png"))
	{
		// Fallback
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void HealthPotion::update(float deltaTime)
{
	x += velocityX * deltaTime;
	sprite.setPosition(x, y);

	if (x < -100.0f)
		isActive = false;
}

void HealthPotion::draw(sf::RenderWindow& window)
{
	if (isActive)
		window.draw(sprite);
}
