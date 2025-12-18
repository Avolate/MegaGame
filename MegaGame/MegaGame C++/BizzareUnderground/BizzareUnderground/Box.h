#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>
class Box
{
private:
    float x, y;
    sf::RectangleShape shape;

    // ========== СПРАЙТ ==========
    sf::Texture boxTexture;
    sf::Sprite boxSprite;
    bool spriteLoaded;
    // =============================

    sf::Vector2f velocity;
    bool onGround;
    const float GRAVITY = 500.0f;

public:
    Box(float startX, float startY);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    void setPosition(float newX, float newY);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void stopVerticalVelocity();
    void stopHorizontalVelocity();
    void setOnGround(bool ground);
};