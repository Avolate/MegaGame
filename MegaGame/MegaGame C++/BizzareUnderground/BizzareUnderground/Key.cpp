#include "Key.h"

sf::Texture Key::keyTexture;

Key::Key(float startX, float startY)
    : GameObject(startX, startY), spriteLoaded(false), collected(false)
{
    shape.setSize(sf::Vector2f(SIZE, SIZE));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Transparent);  

    keySprite.setTexture(keyTexture);
    float scale = (SIZE * 3.0f) / keyTexture.getSize().x;  
    keySprite.setScale(scale, scale);
    keySprite.setPosition(x, y);
    spriteLoaded = true;
}

void Key::loadKeyTexture()
{
    keyTexture.loadFromFile("../x64/Debug/key.png");
    keyTexture.loadFromFile("../../x64/Debug/key.png");
}

void Key::update(float deltaTime)
{
    // Ключи статичны - ничего не делаем
}

void Key::draw(sf::RenderWindow& window)
{
    if (!collected)
    {
        window.draw(shape);
        if (spriteLoaded)
        {
            window.draw(keySprite);
        }
    }
}

void Key::collect()
{
    collected = true;
}

bool Key::isCollected() const
{
    return collected;
}
