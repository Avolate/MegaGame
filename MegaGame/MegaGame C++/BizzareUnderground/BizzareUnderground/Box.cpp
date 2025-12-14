#include "Box.h"

Box::Box(float x, float y)
    : gravity(1000.0f), maxFallSpeed(1000.0f), isOnGround(false)
{
    // Создаём коробку (размер 30x30 - половина персонажа)
    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setPosition(x, y);
    body.setFillColor(sf::Color::White);  // Белая коробка
    
    velocity = sf::Vector2f(0.0f, 0.0f);
}

void Box::update(float deltaTime)
{
    // Применение гравитации
    if (!isOnGround)
    {
        velocity.y += gravity * deltaTime;
        if (velocity.y > maxFallSpeed)
            velocity.y = maxFallSpeed;
    }
    else
    {
        // Если на земле, обнуляем вертикальную скорость
        if (velocity.y > 0.0f)
            velocity.y = 0.0f;
    }
    
    // Обновление позиции
    sf::Vector2f newPos = body.getPosition();
    newPos.x += velocity.x * deltaTime;
    newPos.y += velocity.y * deltaTime;
    
    // Проверка границ экрана
    if (newPos.x < 0)
        newPos.x = 0;
    if (newPos.x + body.getSize().x > 1200)
        newPos.x = 1200 - body.getSize().x;
    
    // Если коробка упала ниже экрана, ставим её на начальную позицию
    if (newPos.y > 800)
    {
        newPos.y = 600;
        newPos.x = 1000;
        velocity = sf::Vector2f(0.0f, 0.0f);
    }
    
    body.setPosition(newPos);
}

void Box::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::FloatRect Box::getBounds() const
{
    return body.getGlobalBounds();
}

sf::Vector2f Box::getPosition() const
{
    return body.getPosition();
}

void Box::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Box::setVelocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Box::getVelocity() const
{
    return velocity;
}

void Box::setOnGround(bool grounded)
{
    isOnGround = grounded;
}

bool Box::getIsOnGround() const
{
    return isOnGround;
}

void Box::stopVerticalVelocity()
{
    velocity.y = 0.0f;
}

void Box::stopHorizontalVelocity()
{
    velocity.x = 0.0f;
}
