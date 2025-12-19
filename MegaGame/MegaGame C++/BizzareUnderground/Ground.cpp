#include "Ground.h"

sf::Texture Ground::groundTexture;

Ground::Ground(float startX, float startY, float w, float h)
    : GameObject(startX, startY), width(w), height(h), spriteLoaded(false)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Cyan);

    // ========== СПРАЙТ БЕЗ РАСТЯГИВАНИЯ ==========
    groundSprite.setTexture(groundTexture);
    // НЕ масштабируем спрайт - оставляем оригинальный размер
    // спрайт будет обрезан по размеру объекта благодаря маске
    groundSprite.setPosition(x, y);

    // Устанавливаем область видимости спрайта (обрезка)
    groundSprite.setTextureRect(sf::IntRect(0, 0, (int)width, (int)height));

    spriteLoaded = true;
    // ============================================
}

void Ground::loadGroundTexture()
{
    groundTexture.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\BizzareUnderground\\assets\\ground.png");
    groundTexture.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\BizzareUnderground\\assets\\ground.png");
}

void Ground::update(float deltaTime)
{
    // Платформы статичны - ничего не делаем
}

void Ground::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    if (spriteLoaded)
    {
        window.draw(groundSprite);
    }
}
