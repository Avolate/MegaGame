#pragma once

#include "GameObject.h"

class Door : public GameObject
{
private:
    sf::Texture doorTexture;
    sf::Sprite doorSprite;
    bool spriteLoaded;

    bool isOpen;
    const float WIDTH = 60.0f;
    const float HEIGHT = 80.0f;

public:
    Door(float startX, float startY);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void open();
    void close();
    bool getIsOpen() const;
};
