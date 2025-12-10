#include "Archer.h"

Archer::Archer() : GameObject(), mouseX(800.0f), mouseY(400.0f)
{
	x = 800.0f;
	y = 400.0f;
	velocityX = 0.0f;
	velocityY = 0.0f;
	isActive = true;

	// Загружаем спрайт игрока (john_idle 36x37)
	if (!textureJohn.loadFromFile("assets/john_idle.png"))
	{
		// Fallback
	}
	spritePlayer.setTexture(textureJohn);
	spritePlayer.setScale(2.0f, 2.0f);
	spritePlayer.setPosition(x, y);

	// Загружаем спрайт платформы (landpl 198x154)
	if (!texturePlatform.loadFromFile("assets/landpl.png"))
	{
		// Fallback
	}
	spritePlatform.setTexture(texturePlatform);
	spritePlatform.setPosition(x - 80, y + 20);
}

void Archer::setMousePos(float mx, float my)
{
	mouseX = mx;
	mouseY = my;
}

void Archer::update(float deltaTime)
{
	// ИСПРАВЛЕНО: Используем прямое движение вместо плавного
	// Это устраняет дрожание/дергание при движении
	const float minY = 0.0f;
	const float maxY = 800.0f - 100.0f;
	const float minX = 80.0f;  // Граница замка (430 + небольшой отступ)
	const float maxX = 1500.0f - 150.0f;

	// Прямое назначение позиции (без lerp - это избавляет от дрожания)
	x = mouseX;
	y = mouseY;

	// Применяем ограничения
	if (x < minX) x = minX;
	if (x > maxX) x = maxX;
	if (y < minY) y = minY;
	if (y > maxY) y = maxY;

	spritePlayer.setPosition(x, y);
	spritePlatform.setPosition(x - 80, y + 20);
}

void Archer::draw(sf::RenderWindow& window)
{
	window.draw(spritePlatform);
	window.draw(spritePlayer);
}
