#pragma once

#include "GameObject.h"

class Box : public GameObject
{
private:
    sf::Texture boxTexture;
    sf::Sprite boxSprite;
    bool spriteLoaded;

    sf::Vector2f velocity;
    bool onGround;
    const float GRAVITY = 500.0f;

public:
    Box(float startX, float startY);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void setPosition(float newX, float newY) override;
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void stopVerticalVelocity();
    void stopHorizontalVelocity();
    void setOnGround(bool ground);
};
