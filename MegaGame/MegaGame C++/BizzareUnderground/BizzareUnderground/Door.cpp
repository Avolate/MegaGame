#include "Door.h"

Door::Door(float startX, float startY)
    : x(startX), y(startY), isOpen(false), spriteLoaded(false)
{
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);

    // ========== ЗАГРУЖАЕМ СПРАЙТ ==========
    doorTexture.loadFromFile("../x64/Debug/door.png");
    doorTexture.loadFromFile("../../x64/Debug/door.png");
    spriteLoaded = true;
    doorSprite.setTexture(doorTexture);

    // Масштабируем спрайт по размеру Door (60x80)
    float scaleX = WIDTH / doorTexture.getSize().x;
    float scaleY = HEIGHT / doorTexture.getSize().y;
    doorSprite.setScale(scaleX, scaleY);

    doorSprite.setPosition(x, y);
}

void Door::open()
{
    isOpen = true;
    shape.setFillColor(sf::Color::Green);
}

void Door::close()
{
    isOpen = false;
    shape.setFillColor(sf::Color::Blue);
}

bool Door::getIsOpen() const
{
    return isOpen;
}

sf::FloatRect Door::getBounds() const
{
    return shape.getGlobalBounds();
}

void Door::draw(sf::RenderWindow& window)
{
    // Рисуем синий/зеленый прямоугольник сзади
    window.draw(shape);

    // ========== РИСУЕМ СПРАЙТ ПОВЕРХ ==========
    if (spriteLoaded)
    {
        window.draw(doorSprite);
    }
    // =========================================
}