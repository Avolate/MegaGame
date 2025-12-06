#include "Game.h"

Game::Game() : player(100.0f, 400.0f)
{
    window.create(sf::VideoMode(static_cast<unsigned int>(WINDOW_WIDTH),
        static_cast<unsigned int>(WINDOW_HEIGHT)),
        "Platformer Game");
    window.setFramerateLimit(60);

    initializeLevel();
}

void Game::initializeLevel()
{
    // Создаем платформы
    // Нижний пол
    grounds.emplace_back(0.0f, 700.0f, 1200.0f, 100.0f);

    // Платформы посередине
    grounds.emplace_back(200.0f, 550.0f, 300.0f, 40.0f);
    grounds.emplace_back(700.0f, 550.0f, 300.0f, 40.0f);

    // Платформы выше
    grounds.emplace_back(100.0f, 400.0f, 200.0f, 40.0f);
    grounds.emplace_back(900.0f, 400.0f, 200.0f, 40.0f);
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    float deltaTime = gameClock.restart().asSeconds();
    player.update(deltaTime);
    checkCollisions();
}

void Game::checkCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();
    bool isColliding = false;

    for (const auto& ground : grounds)
    {
        sf::FloatRect groundBounds = ground.getBounds();

        // Проверяем пересечение
        if (playerBounds.intersects(groundBounds))
        {
            // Проверяем, падает ли персонаж сверху
            float playerBottomOld = playerBounds.top + playerBounds.height;
            float groundTop = groundBounds.top;

            // Если персонаж был выше и пересекается, то он приземляется
            if (playerBottomOld <= groundTop + 10.0f)
            {
                player.setOnGround(true);
                isColliding = true;
                break;
            }
        }
    }

    if (!isColliding)
    {
        player.setOnGround(false);
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    // Рисуем все платформы
    for (auto& ground : grounds)
    {
        ground.draw(window);
    }

    // Рисуем игрока
    player.draw(window);

    window.display();
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

bool Game::isRunning() const
{
    return window.isOpen();
}