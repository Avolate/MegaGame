#include "Dart.h"

Dart::Dart(float x, float y, float directionX) : isActive(true)
{
    // Создаём дротик (маленький прямоугольник 15x5)
    body.setSize(sf::Vector2f(15.0f, 5.0f));
    body.setPosition(x, y);
    body.setFillColor(sf::Color::Magenta);  // Фиолетовый дротик
    
    // Скорость дротика (600 px/s)
    velocity = sf::Vector2f(600.0f * directionX, 0.0f);
}

void Dart::update(float deltaTime)
{
    if (!isActive)
        return;
    
    // Обновление позиции
    sf::Vector2f newPos = body.getPosition();
    newPos.x += velocity.x * deltaTime;
    
    // Если дротик вышел за границы экрана, уничтожаем его
    if (newPos.x < 0 || newPos.x > 1200)
    {
        isActive = false;
        return;
    }
    
    body.setPosition(newPos);
}

void Dart::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(body);
    }
}

sf::FloatRect Dart::getBounds() const
{
    return body.getGlobalBounds();
}

bool Dart::getIsActive() const
{
    return isActive;
}

void Dart::destroy()
{
    isActive = false;
}
