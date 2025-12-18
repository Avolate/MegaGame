#pragma once

#include "GameObject.h"

class Dart : public GameObject
{
private:
    sf::Vector2f velocity;
    bool isActive;

public:
    Dart(float x, float y, float directionX);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    bool getIsActive() const;
    void destroy();
};
