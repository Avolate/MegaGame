#pragma once

#include "GameObject.h"

class Archer : public GameObject
{
public:
	Archer();
	virtual ~Archer() = default;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void setMousePos(float mouseX, float mouseY);

	sf::FloatRect getBounds() const { return spritePlayer.getGlobalBounds(); }
	sf::FloatRect getPlatformBounds() const { return spritePlatform.getGlobalBounds(); }
private:
	sf::Texture textureJohn;
	sf::Texture texturePlatform;
	sf::Sprite spritePlayer;
	sf::Sprite spritePlatform;
	float mouseX, mouseY;
};
