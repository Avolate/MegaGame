#pragma once

#include "GameObject.h"

class BossBoulder : public GameObject
{
public:
	BossBoulder();
	virtual ~BossBoulder() = default;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	int getHealth() const { return health; }
	void takeDamage(int damage) { health -= damage; }

	sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

private:
	sf::Texture texture;
	sf::Sprite sprite;
	int health;
};
