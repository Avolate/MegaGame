#pragma once

#include "GameObject.h"

class Boulder : public GameObject
{
public:
	Boulder();
	virtual ~Boulder() = default;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

private:
	sf::Texture texture;
	sf::Sprite sprite;
};
