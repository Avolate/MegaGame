#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Button
{
private:
    sf::RectangleShape shape;
    bool isPressed;

public:
    Button(float x, float y);
    
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    
    bool getIsPressed() const;
    void press();
    void release();
};
