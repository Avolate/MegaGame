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

    // Добавляем шипы (размер 40x40)
    spikes.emplace_back(350.0f, 660.0f, 40.0f);  // Левый нижний шип
    spikes.emplace_back(800.0f, 660.0f, 40.0f);  // Правый нижний шип
    spikes.emplace_back(250.0f, 510.0f, 40.0f);  // Левый средний шип
    spikes.emplace_back(900.0f, 510.0f, 40.0f);  // Правый средний шип
    spikes.emplace_back(500.0f, 360.0f, 40.0f);  // Центральный верхний шип
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

    // Проверка столкновения с платформами
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

    // Проверка столкновения с шипами (смерть)
    for (const auto& spike : spikes)
    {
        if (playerBounds.intersects(spike.getBounds()))
        {
            player.respawn();
            return;  // Выходим, чтобы не проверять остальные шипы
        }
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

    // Рисуем все шипы
    for (auto& spike : spikes)
    {
        spike.draw(window);
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