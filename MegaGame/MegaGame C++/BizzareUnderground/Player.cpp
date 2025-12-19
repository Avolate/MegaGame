#include "Player.h"

sf::Texture Player::playerTexture;
bool Player::textureLoaded = false;
bool Player::textureInitialized = false;

void Player::loadPlayerTexture()
{
    if (textureInitialized)
        return;

    textureInitialized = true;

    // ========== ЗАГРУЖАЕМ СПРАЙТ ОДИН РАЗ ==========
    if (playerTexture.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\BizzareUnderground\\assets\\player.png"))
    {
        textureLoaded = true;
    }
    else
    {
        textureLoaded = false;

    }
    // ===============================================
}

Player::Player(float startX, float startY)
    : x(startX), y(startY), velocityX(0.0f), velocityY(0.0f), onGround(false)
{
    shape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(x, y);

    // ========== ИНИЦИАЛИЗИРУЕМ СПРАЙТ ==========
    initSprite();
    // ==========================================
}

void Player::initSprite()
{
    if (textureLoaded)
    {
        // Привязываем текстуру к спрайту
        playerSprite.setTexture(playerTexture);

        // Масштабируем спрайт по размеру плеера
        unsigned int texWidth = playerTexture.getSize().x;
        unsigned int texHeight = playerTexture.getSize().y;

        if (texWidth > 0 && texHeight > 0)
        {
            float scaleX = WIDTH / texWidth;
            float scaleY = HEIGHT / texHeight;
            playerSprite.setScale(scaleX, scaleY);
        }

        playerSprite.setPosition(x, y);
    }
    else
    {

    }
}

void Player::handleInput()
{
    // ========== ДВИЖЕНИЕ ВЛЕВО-ВПРАВО ==========
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocityX = -MOVE_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocityX = MOVE_SPEED;
    }
    else
    {
        velocityX = 0.0f;
    }
    // ===========================================

    // ========== ПРЫГАНИЕ ==========
    if (onGround)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocityY = -JUMP_FORCE;
            onGround = false;
        }
    }
    // ==============================
}

void Player::update(float deltaTime)
{
    handleInput();

    // Применяем гравитацию
    velocityY += GRAVITY * deltaTime;

    // Ограничиваем максимальную скорость падения
    if (velocityY > 600.0f)
        velocityY = 600.0f;

    // Обновляем позицию
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;

    // Границы экрана (слева-справа)
    if (x < 0.0f)
        x = 0.0f;
    if (x + WIDTH > 1200.0f)
        x = 1200.0f - WIDTH;

    // Если персонаж упал ниже экрана - перезагружаем
    if (y > 800.0f)
    {
        x = 100.0f;
        y = 550.0f;
        velocityX = 0.0f;
        velocityY = 0.0f;
    }

    // Обновляем позицию прямоугольника
    shape.setPosition(x, y);

    // Обновляем позицию спрайта
    if (textureLoaded)
    {
        playerSprite.setPosition(x, y);
    }
}

void Player::draw(sf::RenderWindow& window)
{
    // Рисуем синий прямоугольник
    window.draw(shape);

    // Рисуем спрайт поверх
    if (textureLoaded)
    {
        window.draw(playerSprite);
    }
}

void Player::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
    shape.setPosition(x, y);

    if (textureLoaded)
    {
        playerSprite.setPosition(x, y);
    }
}

void Player::setOnGround(bool ground)
{
    onGround = ground;
}

void Player::stopVerticalVelocity()
{
    velocityY = 0.0f;
}

void Player::stopHorizontalVelocity()
{
    velocityX = 0.0f;
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();
}