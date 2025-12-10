#include "Castle.h"

Castle::Castle() : GameObject(), health(3)
{
	x = -200.0f;
	y = 0.0f;
	velocityX = 0.0f;
	velocityY = 0.0f;
	isActive = true;

	// Загружаем спрайт замка (castle 430x830)
	if (!texture.loadFromFile("assets/castle.png"))
	{
		// Fallback
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Castle::update(float deltaTime)
{
	// Замок статичен
}

void Castle::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
