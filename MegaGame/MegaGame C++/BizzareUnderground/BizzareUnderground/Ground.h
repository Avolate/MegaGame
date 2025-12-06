#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Ground
{
private:
    sf::RectangleShape shape;

public:
    Ground(float x, float y, float width, float height);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};
