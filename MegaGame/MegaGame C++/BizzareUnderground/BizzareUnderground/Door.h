#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Door
{
private:
    float x, y;
    sf::RectangleShape shape;

    // ========== СПРАЙТ ==========
    sf::Texture doorTexture;
    sf::Sprite doorSprite;
    bool spriteLoaded;
    // =============================

    bool isOpen;
    const float WIDTH = 60.0f;
    const float HEIGHT = 80.0f;

public:
    Door(float startX, float startY);

    void open();
    void close();
    bool getIsOpen() const;
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
};