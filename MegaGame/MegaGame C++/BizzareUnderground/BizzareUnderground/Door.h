#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Door
{
private:
    sf::RectangleShape shape;
    bool isOpen;  // Открыта ли дверь

public:
    Door(float x, float y);
    
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    
    bool getIsOpen() const;
    void open();
    void close();
};
