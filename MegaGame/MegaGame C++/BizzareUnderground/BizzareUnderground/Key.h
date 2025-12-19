#pragma once

#include "GameObject.h"

class Key : public GameObject
{
private:
    static sf::Texture keyTexture;
    sf::Sprite keySprite;
    bool spriteLoaded;

    const float SIZE = 20.0f;

public:
    Key(float startX, float startY);

    static void loadKeyTexture();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void collect();
    bool isCollected() const;

private:
    bool collected;
};
