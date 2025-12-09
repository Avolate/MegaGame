#include "Button.h"

Button::Button(float x, float y) : isPressed(false)
{
    // Создаём кнопку (оранжевый квадрат 40x20)
    shape.setSize(sf::Vector2f(40.0f, 20.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);  // Жёлтая, когда не нажата
}

void Button::draw(sf::RenderWindow& window)
{
    // Меняем цвет в зависимости от нажатия
    if (isPressed)
    {
        shape.setFillColor(sf::Color::Red);  // Красная, когда нажата
    }
    else
    {
        shape.setFillColor(sf::Color::Yellow);  // Жёлтая, когда отпущена
    }
    
    window.draw(shape);
}

sf::FloatRect Button::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Button::getIsPressed() const
{
    return isPressed;
}

void Button::press()
{
    isPressed = true;
}

void Button::release()
{
    isPressed = false;
}
