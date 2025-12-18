#include "Spike.h"

Spike::Spike(float startX, float startY, float spikeSize)
    : GameObject(startX, startY), size(spikeSize)
{
    // Создаём белый треугольник (равносторонний)
    triangle.setPointCount(3);  // 3 точки = треугольник

    // Вершины треугольника
    triangle.setPoint(0, sf::Vector2f(size / 2.0f, 0.0f));           // Верхняя вершина
    triangle.setPoint(1, sf::Vector2f(size, size));                  // Правая нижняя вершина
    triangle.setPoint(2, sf::Vector2f(0.0f, size));                  // Левая нижняя вершина

    // Стиль
    triangle.setFillColor(sf::Color::White);
    triangle.setPosition(startX, startY);
}

void Spike::update(float deltaTime)
{
    // Шипы статичны - ничего не делаем
}

void Spike::draw(sf::RenderWindow& window)
{
    window.draw(triangle);
}

sf::FloatRect Spike::getBounds() const
{
    return triangle.getGlobalBounds();
}
