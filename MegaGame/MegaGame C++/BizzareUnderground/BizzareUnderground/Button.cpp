#include "Button.h"

Button::Button(float x, float y)
    : GameObject(x, y), isPressed(false)
{
    // Прямоугольник 40x8 как и раньше
    shape.setSize(sf::Vector2f(40.0f, 8.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow); // Жёлтая, когда не нажата
}

void Button::update(float deltaTime)
{
    // Кнопка статична, логики обновления нет
}

void Button::draw(sf::RenderWindow& window)
{
    // Меняем цвет в зависимости от нажатия
    if (isPressed)
        shape.setFillColor(sf::Color::Transparent); // Когда нажата
    else
        shape.setFillColor(sf::Color::Red);          // Когда отпущена

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
