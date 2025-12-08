#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Key
{
private:
    sf::RectangleShape shape;
    bool collected;  // Собран ли ключ

public:
    Key(float x, float y);
    
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    
    bool isCollected() const;
    void collect();
};
