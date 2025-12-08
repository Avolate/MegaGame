#pragma once
#include "GameObject.h"

class Archer : public GameObject
{
public:
    Archer();
    virtual ~Archer() = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::RectangleShape shape;
};
