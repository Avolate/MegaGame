#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
    float x, y;
    float velocityX, velocityY;
    sf::RectangleShape shape;

    // ========== СПРАЙТ ==========
    static sf::Texture playerTexture;
    static bool textureLoaded;
    static bool textureInitialized;
    sf::Sprite playerSprite;
    // =============================

    bool onGround;
    const float WIDTH = 40.0f;
    const float HEIGHT = 60.0f;
    const float GRAVITY = 1000.0f;
    const float JUMP_FORCE = 570.0f;
    const float MOVE_SPEED = 250.0f;

public:
    Player(float startX, float startY);

    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setPosition(float newX, float newY);
    void setOnGround(bool ground);
    void stopVerticalVelocity();
    void stopHorizontalVelocity();

    sf::FloatRect getBounds() const;

    // Статический метод для загрузки текстуры один раз
    static void loadPlayerTexture();

    // ЭТОТ МЕТОД ДОЛЖЕН БЫТЬ PUBLIC!
    void initSprite();
};