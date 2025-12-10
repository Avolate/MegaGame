#include "Boulder.h"
#include <cstdlib>

Boulder::Boulder() : GameObject()
{
	x = 1500.0f;
	y = static_cast<float>(rand() % (800 - 64));
	// Рандомная скорость: от -300 до -500
	velocityX = -300.0f - (rand() % 200);
	velocityY = 0.0f;
	isActive = true;

	// Загружаем спрайт метеора (stone 64x64)
	if (!texture.loadFromFile("assets/stone.png"))
	{
		// Fallback
	}
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void Boulder::update(float deltaTime)
{
	x += velocityX * deltaTime;
	sprite.setPosition(x, y);

	// Удаляем, если вышел за экран влево
	if (x < -100.0f)
		isActive = false;
}

void Boulder::draw(sf::RenderWindow& window)
{
	if (isActive)
		window.draw(sprite);
}
