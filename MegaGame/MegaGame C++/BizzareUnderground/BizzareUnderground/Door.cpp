#include "Door.h"

Door::Door(float x, float y) : isOpen(false)
{
    // Создаём прямоугольник двери
    shape.setSize(sf::Vector2f(50.0f, 80.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Magenta);  // Закрытая дверь - фиолетовая
}

void Door::draw(sf::RenderWindow& window)
{
    // Меняем цвет в зависимости от открыта ли дверь
    if (isOpen)
    {
        shape.setFillColor(sf::Color::Green);  // Открытая дверь - зелёная
    }
    else
    {
        shape.setFillColor(sf::Color::Magenta);  // Закрытая дверь - фиолетовая
    }
    
    window.draw(shape);
}

sf::FloatRect Door::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Door::getIsOpen() const
{
    return isOpen;
}

void Door::open()
{
    isOpen = true;
}

void Door::close()
{
    isOpen = false;
}
