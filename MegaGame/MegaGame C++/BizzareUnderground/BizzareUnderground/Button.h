#pragma once

#include "GameObject.h"

class Button : public GameObject
{
private:
    bool isPressed;

public:
    Button(float x, float y);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    bool getIsPressed() const;
    void press();
    void release();
};
