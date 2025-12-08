#include "Key.h"

Key::Key(float x, float y) : collected(false)
{
    // Создаём квадратик ключа
    shape.setSize(sf::Vector2f(20.0f, 20.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);  // Жёлтые ключи
}

void Key::draw(sf::RenderWindow& window)
{
    // Рисуем только если ключ не собран
    if (!collected)
    {
        window.draw(shape);
    }
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
