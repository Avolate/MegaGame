#include "Game.h"

Game::Game() : player(100.0f, 400.0f), box(600.0f, 300.0f),
button(550.0f, 680.0f), door(1050.0f, 620.0f),
keysCollected(0), isRightSpikeActive(true)
{
    window.create(sf::VideoMode(static_cast<unsigned int>(WINDOW_WIDTH),
        static_cast<unsigned int>(WINDOW_HEIGHT)),
        "Platformer Game");
    window.setFramerateLimit(60);

    initializeLevel();
}

void Game::initializeLevel()
{
    grounds.clear();
    spikes.clear();
    keys.clear();
    keysCollected = 0;
    door.close();
    isRightSpikeActive = true;
    button.release();

    grounds.emplace_back(0.0f, 700.0f, 1200.0f, 100.0f);
    grounds.emplace_back(200.0f, 550.0f, 300.0f, 5.0f);
    grounds.emplace_back(700.0f, 550.0f, 300.0f, 5.0f);
    grounds.emplace_back(100.0f, 400.0f, 200.0f, 5.0f);
    grounds.emplace_back(900.0f, 400.0f, 200.0f, 5.0f);
    grounds.emplace_back(1000.0f, 10.0f, 5.0f, 580.0f);

    spikes.emplace_back(350.0f, 660.0f, 40.0f);  // Левый нижний
    spikes.emplace_back(800.0f, 600.0f, 100.0f);  // Правый нижний (управляется кнопкой)
    spikes.emplace_back(250.0f, 510.0f, 40.0f);
    spikes.emplace_back(900.0f, 510.0f, 40.0f);
    spikes.emplace_back(500.0f, 360.0f, 40.0f);

    keys.emplace_back(150.0f, 350.0f);
    keys.emplace_back(950.0f, 350.0f);
    keys.emplace_back(600.0f, 500.0f);
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
    box.update(deltaTime);
    checkCollisions();
}

void Game::checkCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();
    sf::FloatRect boxBounds = box.getBounds();
    sf::FloatRect buttonBounds = button.getBounds();

    bool isPlayerColliding = false;
    bool isBoxColliding = false;
    bool isButtonPressed = false;

    // ==================== ПРОВЕРКА НАЖАТИЯ КНОПКИ ====================
    if (playerBounds.intersects(buttonBounds) || boxBounds.intersects(buttonBounds))
    {
        button.press();
        isRightSpikeActive = false;
        isButtonPressed = true;
    }
    else
    {
        button.release();
        isRightSpikeActive = true;
    }

    // ==================== КОЛЛИЗИИ ПЕРСОНАЖА С ПЛАТФОРМАМИ ====================
    for (const auto& ground : grounds)
    {
        sf::FloatRect groundBounds = ground.getBounds();

        if (playerBounds.intersects(groundBounds))
        {
            float overlapLeft = (playerBounds.left + playerBounds.width) - groundBounds.left;
            float overlapRight = (groundBounds.left + groundBounds.width) - playerBounds.left;
            float overlapTop = (playerBounds.top + playerBounds.height) - groundBounds.top;
            float overlapBottom = (groundBounds.top + groundBounds.height) - playerBounds.top;

            float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                std::min(overlapTop, overlapBottom));

            if (minOverlap == overlapTop &&
                playerBounds.top + playerBounds.height / 2.0f < groundBounds.top)
            {
                player.stopVerticalVelocity();
                player.setPosition(playerBounds.left,
                    groundBounds.top - playerBounds.height);
                player.setOnGround(true);
                isPlayerColliding = true;
                break;
            }
            else if (minOverlap == overlapBottom)
            {
                player.stopVerticalVelocity();
                player.setPosition(playerBounds.left,
                    groundBounds.top + groundBounds.height);
                isPlayerColliding = true;
                break;
            }
            else if (minOverlap == overlapLeft)
            {
                player.stopHorizontalVelocity();
                player.setPosition(groundBounds.left - playerBounds.width,
                    playerBounds.top);
                isPlayerColliding = true;
                break;
            }
            else if (minOverlap == overlapRight)
            {
                player.stopHorizontalVelocity();
                player.setPosition(groundBounds.left + groundBounds.width,
                    playerBounds.top);
                isPlayerColliding = true;
                break;
            }
        }
    }

    if (!isPlayerColliding)
        player.setOnGround(false);

    // ==================== КОЛЛИЗИИ КОРОБКИ С ПЛАТФОРМАМИ ====================
    for (const auto& ground : grounds)
    {
        sf::FloatRect groundBounds = ground.getBounds();

        if (boxBounds.intersects(groundBounds))
        {
            float overlapLeft = (boxBounds.left + boxBounds.width) - groundBounds.left;
            float overlapRight = (groundBounds.left + groundBounds.width) - boxBounds.left;
            float overlapTop = (boxBounds.top + boxBounds.height) - groundBounds.top;
            float overlapBottom = (groundBounds.top + groundBounds.height) - boxBounds.top;

            float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                std::min(overlapTop, overlapBottom));

            if (minOverlap == overlapTop &&
                boxBounds.top + boxBounds.height / 2.0f < groundBounds.top)
            {
                box.stopVerticalVelocity();
                box.setPosition(boxBounds.left,
                    groundBounds.top - boxBounds.height);
                box.setOnGround(true);
                isBoxColliding = true;
                break;
            }
            else if (minOverlap == overlapBottom)
            {
                box.stopVerticalVelocity();
                box.setPosition(boxBounds.left,
                    groundBounds.top + groundBounds.height);
                isBoxColliding = true;
                break;
            }
            else if (minOverlap == overlapLeft)
            {
                box.stopHorizontalVelocity();
                box.setPosition(groundBounds.left - boxBounds.width,
                    boxBounds.top);
                isBoxColliding = true;
                break;
            }
            else if (minOverlap == overlapRight)
            {
                box.stopHorizontalVelocity();
                box.setPosition(groundBounds.left + groundBounds.width,
                    boxBounds.top);
                isBoxColliding = true;
                break;
            }
        }
    }

    if (!isBoxColliding)
        box.setOnGround(false);

    // ==================== СТОЛКНОВЕНИЕ ПЕРСОНАЖА И КОРОБКИ ====================
    playerBounds = player.getBounds();
    boxBounds = box.getBounds();

    if (playerBounds.intersects(boxBounds))
    {
        float overlapLeft = (playerBounds.left + playerBounds.width) - boxBounds.left;
        float overlapRight = (boxBounds.left + boxBounds.width) - playerBounds.left;
        float overlapTop = (playerBounds.top + playerBounds.height) - boxBounds.top;
        float overlapBottom = (boxBounds.top + boxBounds.height) - playerBounds.top;

        float minOverlap = std::min(std::min(overlapLeft, overlapRight),
            std::min(overlapTop, overlapBottom));

        if (minOverlap == overlapTop &&
            playerBounds.top + playerBounds.height / 2.0f < boxBounds.top)
        {
            player.stopVerticalVelocity();
            player.setPosition(playerBounds.left,
                boxBounds.top - playerBounds.height);
            player.setOnGround(true);
        }
        else if (minOverlap == overlapBottom)
        {
            player.stopVerticalVelocity();
        }
        else if (minOverlap == overlapLeft)
        {
            float boxSpeed = 300.0f;
            box.setVelocity(boxSpeed, box.getVelocity().y);
            player.stopHorizontalVelocity();
        }
        else if (minOverlap == overlapRight)
        {
            float boxSpeed = 300.0f;
            box.setVelocity(-boxSpeed, box.getVelocity().y);
            player.stopHorizontalVelocity();
        }
    }
    else
    {
        box.setVelocity(0.0f, box.getVelocity().y);
    }

    // ==================== СТОЛКНОВЕНИЕ С ШИПАМИ (ТОЛЬКО АКТИВНЫЕ) ====================
    playerBounds = player.getBounds();

    // Проверяем все шипы, но пропускаем индекс 1 (правый нижний) если он неактивен
    for (int i = 0; i < spikes.size(); i++)
    {
        // Пропускаем правый нижний шип (индекс 1), если он неактивен
        if (i == 1 && !isRightSpikeActive)
            continue;

        if (playerBounds.intersects(spikes[i].getBounds()))
        {
            resetKeysAndDoor();
            player.respawn();
            box.setPosition(600.0f, 300.0f);
            box.setVelocity(0.0f, 0.0f);
            return;
        }
    }

    // ==================== СБОР КЛЮЧЕЙ ====================
    for (auto& key : keys)
    {
        if (!key.isCollected() && playerBounds.intersects(key.getBounds()))
        {
            key.collect();
            keysCollected++;

            if (keysCollected == 3)
                door.open();
        }
    }

    // ==================== ДВЕРЬ ====================
    if (door.getIsOpen() && playerBounds.intersects(door.getBounds()))
        resetLevel();
}

void Game::resetKeysAndDoor()
{
    keysCollected = 0;
    door.close();
    keys.clear();
    keys.emplace_back(150.0f, 350.0f);
    keys.emplace_back(950.0f, 350.0f);
    keys.emplace_back(600.0f, 500.0f);
}

void Game::resetLevel()
{
    player.respawn();
    box.setPosition(600.0f, 300.0f);
    box.setVelocity(0.0f, 0.0f);
    initializeLevel();
}

void Game::render()
{
    window.clear(sf::Color::Black);

    for (auto& ground : grounds)
        ground.draw(window);

    for (int i = 0; i < spikes.size(); i++)
    {
        // Рисуем шип только если он активен (или если это не правый нижний шип)
        if (i == 1 && !isRightSpikeActive)
            continue;

        spikes[i].draw(window);
    }

    for (auto& key : keys)
        key.draw(window);

    button.draw(window);
    door.draw(window);
    box.draw(window);
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
