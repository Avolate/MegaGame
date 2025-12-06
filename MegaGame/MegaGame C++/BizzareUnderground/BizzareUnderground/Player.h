#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>

class Player
{
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;

    // Физика
    float moveSpeed;
    float jumpForce;
    float gravity;
    float maxFallSpeed;

    // Состояние
    bool isOnGround;
    float groundY;

    // Начальная позиция для возрождения
    float startX;
    float startY;

public:
    Player(float startX, float startY);

    // Основные методы
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Геттеры
    sf::FloatRect getBounds() const;
    float getY() const;

    // Сеттеры для земли
    void setOnGround(bool grounded);
    void setGroundY(float y);

    // Методы для коррекции позиции при столкновении
    void setPosition(float x, float y);
    void stopVerticalVelocity();
    void stopHorizontalVelocity();

    // Respawn при смерти
    void respawn();
};