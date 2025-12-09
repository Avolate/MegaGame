#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Box
{
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;
    
    // Физика
    float gravity;
    float maxFallSpeed;
    bool isOnGround;

public:
    Box(float x, float y);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    
    void setPosition(float x, float y);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    
    void setOnGround(bool grounded);
    bool getIsOnGround() const;
    
    void stopVerticalVelocity();
    void stopHorizontalVelocity();
};
