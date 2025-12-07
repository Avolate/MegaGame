#include "Spike.h"

Spike::Spike(float x, float y, float size)
{
    // Создаём треугольник (острие вверх)
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(size / 2.0f, 0.0f));        // Вершина вверху
    triangle.setPoint(1, sf::Vector2f(size, size));                 // Нижний правый угол
    triangle.setPoint(2, sf::Vector2f(0.0f, size));                 // Нижний левый угол
    
    triangle.setPosition(x, y);
    triangle.setFillColor(sf::Color::Red);  // Красные шипы
}

void Spike::draw(sf::RenderWindow& window)
{
    window.draw(triangle);
}

sf::FloatRect Spike::getBounds() const
{
    return triangle.getGlobalBounds();
}
