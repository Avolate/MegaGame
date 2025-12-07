#pragma once
#include <SFML/Graphics.hpp>

class Spike
{
private:
    sf::ConvexShape triangle;  // Треугольник для спайка

public:
    Spike(float x, float y, float size);
    
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};
