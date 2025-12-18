#include "Door.h"

Door::Door(float startX, float startY)
    : GameObject(startX, startY), isOpen(false), spriteLoaded(false)
{
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, y);

    // ========== ЗАГРУЖАЕМ СПРАЙТ ==========
    doorTexture.loadFromFile("../x64/Debug/door.png");
    doorTexture.loadFromFile("../../x64/Debug/door.png");
    spriteLoaded = true;
    doorSprite.setTexture(doorTexture);

    float scaleX = WIDTH / doorTexture.getSize().x;
    float scaleY = HEIGHT / doorTexture.getSize().y;
    doorSprite.setScale(scaleX, scaleY);
    doorSprite.setPosition(x, y);
}

void Door::update(float deltaTime)
{
    // Дверь статична - ничего не делаем
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

void Door::draw(sf::RenderWindow& window)
{
    window.draw(shape);

    if (spriteLoaded)
    {
        window.draw(doorSprite);
    }
}
