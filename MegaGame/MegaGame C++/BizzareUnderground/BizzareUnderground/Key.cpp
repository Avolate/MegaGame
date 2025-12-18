#include "Key.h"

// Инициализация статических переменных
sf::Texture Key::keyTexture;
bool Key::textureLoaded = false;
bool Key::textureInitialized = false;

void Key::loadKeyTexture()
{
    if (textureInitialized)
        return;

    textureInitialized = true;

    // ========== ЗАГРУЖАЕМ СПРАЙТ ОДИН РАЗ ==========
    
        if (keyTexture.loadFromFile("../x64/Debug/key.png") ||
            keyTexture.loadFromFile("../../x64/Debug/key.png"))
        {
            textureLoaded = true;
            keyTexture.setRepeated(true);
        }
        else
        {
            textureLoaded = false;
        }
    
    // ===============================================
}

Key::Key(float startX, float startY)
    : x(startX), y(startY), collected(false)
{
    shape.setRadius(RADIUS);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(x, y);

    // ========== СОЗДАЕМ СПРАЙТ С ТЕКСТУРОЙ ==========
    if (textureLoaded)
    {
        keySprite.setTexture(keyTexture, true);

        // Масштабируем спрайт по размеру ключа (20x20 - диаметр круга)
        float diameter = RADIUS * 5;
        float scaleX = diameter / keyTexture.getSize().x;
        float scaleY = diameter / keyTexture.getSize().y;
        keySprite.setScale(scaleX, scaleY);

        keySprite.setPosition(x, y);
    }
    // ================================================
}

void Key::draw(sf::RenderWindow& window)
{
    // Если собран - не рисуем
    if (collected)
        return;

    // Рисуем желтый круг сзади
    window.draw(shape);

    // ========== РИСУЕМ СПРАЙТ ПОВЕРХ ==========
    if (textureLoaded)
    {
        window.draw(keySprite);
    }
    // =========================================
}

sf::FloatRect Key::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Key::isCollected() const
{
    return collected;
}

void Key::collect()
{
    collected = true;
}