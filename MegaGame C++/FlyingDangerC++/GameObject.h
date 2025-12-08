#pragma once
#include <SFML/Graphics.hpp>
//#include <glm/glm.hpp>

class GameObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual void setPosition(float x, float y);
    virtual sf::Vector2f getPosition() const;

    float x, y;
    float velocityX, velocityY;
    bool isActive;
};
