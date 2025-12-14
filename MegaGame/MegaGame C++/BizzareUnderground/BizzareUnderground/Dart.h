#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Dart
{
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;
    bool isActive;  // Активен ли дротик

public:
    Dart(float x, float y, float directionX);  // directionX: -1 для влево, 1 для вправо
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    bool getIsActive() const;
    void destroy();
};
