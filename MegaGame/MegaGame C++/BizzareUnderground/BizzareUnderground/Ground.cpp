#include "Ground.h"

// Инициализация статических переменных
sf::Texture Ground::groundTexture;
bool Ground::textureLoaded = false;
bool Ground::textureInitialized = false;

void Ground::loadGroundTexture()
{
    if (textureInitialized)
        return;

    textureInitialized = true;

    // ========== ЗАГРУЖАЕМ СПРАЙТ ОДИН РАЗ ==========
    if (groundTexture.loadFromFile("../x64/Debug/ground.png") ||
        groundTexture.loadFromFile("../../x64/Debug/ground.png"))
    {
        textureLoaded = true;
        groundTexture.setRepeated(true);
    }

        else
        {
            textureLoaded = false;
        }
    
    // ===============================================
}

Ground::Ground(float startX, float startY, float w, float h)
    : x(startX), y(startY), width(w), height(h)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(x, y);

    // ========== СОЗДАЕМ СПРАЙТ С ТЕКСТУРОЙ ==========
    if (textureLoaded)
    {
        groundSprite.setTexture(groundTexture, true);

        // НЕ масштабируем, а используем TextureRect для обрезки
        groundSprite.setTextureRect(sf::IntRect(0, 0, (int)width, (int)height));

        groundSprite.setPosition(x, y);
    }
    // ================================================
}

void Ground::draw(sf::RenderWindow& window)
{
    // Рисуем черный прямоугольник сзади
    window.draw(shape);

    // ========== РИСУЕМ СПРАЙТ ПОВЕРХ (ОБРЕЗАННЫЙ) ==========
    if (textureLoaded)
    {
        window.draw(groundSprite);
    }
    // ======================================================
}

sf::FloatRect Ground::getBounds() const
{
    return shape.getGlobalBounds();
}