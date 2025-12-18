#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Ground
{
private:
    float x, y, width, height;
    sf::RectangleShape shape;

    // ========== СПРАЙТ ==========
    static sf::Texture groundTexture;
    static bool textureLoaded;
    static bool textureInitialized;
    sf::Sprite groundSprite;
    // =============================

public:
    Ground(float startX, float startY, float w, float h);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    // Статический метод для загрузки текстуры один раз
    static void loadGroundTexture();
};