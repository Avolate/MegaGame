#include "Player.h"

Player::Player(float startX, float startY)
    : moveSpeed(300.0f), jumpForce(500.0f), gravity(1000.0f),
    maxFallSpeed(1000.0f), isOnGround(false), groundY(startY)
{
    // Инициализация тела персонажа
    body.setSize(sf::Vector2f(40.0f, 60.0f));
    body.setPosition(startX, startY);
    body.setFillColor(sf::Color::Blue);

    // Инициализация скорости
    velocity = sf::Vector2f(0.0f, 0.0f);
}

void Player::handleInput()
{
    // Горизонтальное движение
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x = -moveSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x = moveSpeed;
    }
    else
    {
        velocity.x = 0.0f;
    }

    // Прыжок
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isOnGround)
    {
        velocity.y = -jumpForce;
        isOnGround = false;
    }
}

void Player::update(float deltaTime)
{
    handleInput();

    // Применение гравитации
    if (!isOnGround)
    {
        velocity.y += gravity * deltaTime;
        if (velocity.y > maxFallSpeed)
            velocity.y = maxFallSpeed;
    }
    else
    {
        // Если на земле и не прыгаем, обнуляем вертикальную скорость
        if (velocity.y > 0.0f)
            velocity.y = 0.0f;
    }

    // Обновление позиции
    sf::Vector2f newPos = body.getPosition();
    newPos.x += velocity.x * deltaTime;
    newPos.y += velocity.y * deltaTime;

    // Проверка границ экрана (не даем выйти за боковые границы)
    if (newPos.x < 0)
        newPos.x = 0;
    if (newPos.x + body.getSize().x > 1200)
        newPos.x = 1200 - body.getSize().x;

    // Если персонаж упал ниже экрана, возвращаем его на начальную позицию
    if (newPos.y > 800)
    {
        newPos.x = 100;
        newPos.y = 200;
        velocity.y = 0;
    }

    body.setPosition(newPos);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::FloatRect Player::getBounds() const
{
    return body.getGlobalBounds();
}

float Player::getY() const
{
    return body.getPosition().y;
}

void Player::setOnGround(bool grounded)
{
    isOnGround = grounded;
}

void Player::setGroundY(float y)
{
    groundY = y;
}