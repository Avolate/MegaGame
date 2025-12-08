#pragma once
#include "GameObject.h"

class HealthPotion : public GameObject
{
public:
    HealthPotion();
    virtual ~HealthPotion() = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;
};
