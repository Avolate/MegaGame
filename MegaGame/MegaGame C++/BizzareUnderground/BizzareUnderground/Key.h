#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Key
{
private:
    float x, y;
    sf::CircleShape shape;

    // ========== СПРАЙТ ==========
    static sf::Texture keyTexture;
    static bool textureLoaded;
    static bool textureInitialized;
    sf::Sprite keySprite;
    // =============================

    bool collected;
    const float RADIUS = 10.0f;

public:
    Key(float startX, float startY);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isCollected() const;
    void collect();

    // Статический метод для загрузки текстуры один раз
    static void loadKeyTexture();
};