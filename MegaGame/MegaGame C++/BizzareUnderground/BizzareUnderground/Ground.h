#pragma once

#include "GameObject.h"

class Ground : public GameObject
{
private:
    static sf::Texture groundTexture;
    sf::Sprite groundSprite;
    bool spriteLoaded;

    float width, height;

public:
    Ground(float startX, float startY, float w, float h);

    static void loadGroundTexture();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
