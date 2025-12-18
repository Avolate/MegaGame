#include "Box.h"

Box::Box(float startX, float startY)
    : x(startX), y(startY), velocity(0.0f, 0.0f), onGround(false), spriteLoaded(false)
{
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);

    // ========== ЗАГРУЖАЕМ СПРАЙТ ==========
    boxTexture.loadFromFile("../x64/Debug/box.png");
    boxTexture.loadFromFile("../../x64/Debug/box.png");
    spriteLoaded = true;
    boxSprite.setTexture(boxTexture);

    // Масштабируем спрайт по размеру Box (50x50)
    float scaleX = 50.0f / boxTexture.getSize().x;
    float scaleY = 50.0f / boxTexture.getSize().y;
    boxSprite.setScale(scaleX, scaleY);

    boxSprite.setPosition(x, y);
}

void Box::update(float deltaTime)
{
    if (!onGround)
    {
        velocity.y += GRAVITY * deltaTime;
    }

    y += velocity.y * deltaTime;
    x += velocity.x * deltaTime;

    // ========== ОГРАНИЧИВАЕМ ДВИЖЕНИЕ ПО ЭКРАНУ ==========
    const float BOX_WIDTH = 50.0f;
    const float BOX_HEIGHT = 50.0f;
    const float WINDOW_WIDTH = 1200.0f;
    const float WINDOW_HEIGHT = 800.0f;

    // Границы слева и справа
    if (x < 0.0f)
        x = 0.0f;
    if (x + BOX_WIDTH > WINDOW_WIDTH)
        x = WINDOW_WIDTH - BOX_WIDTH;

    // Границы сверху и снизу (если упала за экран - перезагружаем)
    if (y > WINDOW_HEIGHT)
    {
        // Коробка упала - перезагружаем уровень
        // Это обработается в Game.cpp через checkCollisions()
    }
    // ====================================================

    shape.setPosition(x, y);

    // ========== СИНХРОНИЗИРУЕМ СПРАЙТ ==========
    if (spriteLoaded)
    {
        boxSprite.setPosition(x, y);
    }
    // ==========================================
}

void Box::draw(sf::RenderWindow& window)
{
    // Рисуем белый квадрат сзади
    window.draw(shape);

    // ========== РИСУЕМ СПРАЙТ ПОВЕРХ ==========
    if (spriteLoaded)
    {
        window.draw(boxSprite);
    }
    // =========================================
}

sf::FloatRect Box::getBounds() const
{
    return shape.getGlobalBounds();
}

void Box::setPosition(float newX, float newY)
{
    // ========== ОГРАНИЧИВАЕМ ПОЗИЦИЮ ==========
    const float BOX_WIDTH = 50.0f;
    const float BOX_HEIGHT = 50.0f;
    const float WINDOW_WIDTH = 1200.0f;
    const float WINDOW_HEIGHT = 800.0f;

    // Проверяем границы экрана
    if (newX < 0.0f)
        newX = 0.0f;
    if (newX + BOX_WIDTH > WINDOW_WIDTH)
        newX = WINDOW_WIDTH - BOX_WIDTH;

    // newY может быть за пределами (для падения)
    // ==========================================

    x = newX;
    y = newY;
    shape.setPosition(x, y);

    // ========== ОБНОВЛЯЕМ ПОЗИЦИЮ СПРАЙТА ==========
    if (spriteLoaded)
    {
        boxSprite.setPosition(x, y);
    }
    // =============================================
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

void Box::stopVerticalVelocity()
{
    velocity.y = 0.0f;
}

void Box::stopHorizontalVelocity()
{
    velocity.x = 0.0f;
}

void Box::setOnGround(bool ground)
{
    onGround = ground;
}