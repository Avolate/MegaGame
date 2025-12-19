#pragma once

#include "GameObject.h"

class Spike : public GameObject
{
private:
    sf::ConvexShape triangle;
    float size;

public:
    Spike(float startX, float startY, float spikeSize);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
};
