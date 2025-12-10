#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(float startX, float startY);
	virtual ~Projectile() = default;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

private:
	sf::Texture texture;
	sf::Sprite sprite;
};
