#pragma once

#include <SFML/Graphics.hpp>

class FallingObject {
protected:
    sf::Sprite sprite;
    sf::Vector2f position;
    float velocity;
    bool isActive;
    sf::FloatRect bounds;

public:
    FallingObject(float x, float y, float vel);
    virtual ~FallingObject();

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    bool getActive() const;
    void setActive(bool active);
    sf::FloatRect getBounds() const;
};
