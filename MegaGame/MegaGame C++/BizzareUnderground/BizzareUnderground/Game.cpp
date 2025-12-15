#include "Game.h"

Game::Game() : player(100.0f, 550.0f),
button(1100.0f, 680.0f), button2(300.0f, 680.0f), button3(0.0f, 280.0f),
door(590.0f, 30.0f),
keysCollected(0), buttonActivated(false), platformsActive(false),
button3Pressed(false), delayedPlatformActive(false), spawnedBox(nullptr),
gameOver(false), isPaused(false), levelComplete(false)
{
    window.create(sf::VideoMode(static_cast<unsigned int>(WINDOW_WIDTH),
        static_cast<unsigned int>(WINDOW_HEIGHT)),
        "Platformer Game");
    window.setFramerateLimit(60);
    initializeLevel();
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
}

Game::~Game()
{
    if (spawnedBox != nullptr)
    {
        delete spawnedBox;
        spawnedBox = nullptr;
    }
}

void Game::initializeLevel()
{
    grounds.clear();
    temporaryGrounds.clear();
    delayedGrounds.clear();
    spikes.clear();
    keys.clear();
    darts.clear();
    keysCollected = 0;
    door.close();
    buttonActivated = false;
    platformsActive = false;
    button3Pressed = false;
    delayedPlatformActive = false;
    button.release();
    button2.release();
    button3.release();
    dartSpawner.restart();
    delayedPlatformTimer.restart();
    gameOver = false;
    isPaused = false;
    levelComplete = false;

    if (spawnedBox != nullptr)
    {
        delete spawnedBox;
        spawnedBox = nullptr;
    }

    // ========== ВОЗВРАЩАЕМ ПЕРСОНАЖА НА НАЧАЛЬНУЮ ПОЗИЦИЮ ==========
    player.setPosition(PLAYER_START_X, PLAYER_START_Y);
    player.stopVerticalVelocity();
    player.stopHorizontalVelocity();
    // ======================================================================

    grounds.emplace_back(0.0f, 700.0f, 1200.0f, 100.0f);
    grounds.emplace_back(0.0f, 0.0f, 1200.0f, 5.0f);
    grounds.emplace_back(900.0f, 400.0f, 200.0f, 5.0f);
    grounds.emplace_back(1100.0f, 250.0f, 100.0f, 5.0f);
    grounds.emplace_back(1000.0f, 100.0f, 100.0f, 5.0f);
    grounds.emplace_back(1000.0f, 0.0f, 5.0f, 400.0f);
    grounds.emplace_back(580.0f, 450.0f, 150.0f, 5.0f);//правая
    grounds.emplace_back(300.0f, 450.0f, 150.0f, 5.0f);//лквая
    grounds.emplace_back(520.0f, 110.0f, 200.0f, 5.0f);
    grounds.emplace_back(780.0f, 220.0f, 160.0f, 5.0f);
    grounds.emplace_back(0.0f, 300.0f, 200.0f, 5.0f);

    // Временные платформы (активируются при нажатии кнопки 2)
    temporaryGrounds.emplace_back(1100.0f, 550.0f, 300.0f, 5.0f);
    temporaryGrounds.emplace_back(850.0f, 500.0f, 150.0f, 5.0f);

    spikes.emplace_back(200.0f, 660.0f, 40.0f);
    spikes.emplace_back(355.0f, 410.0f, 40.0f);
    spikes.emplace_back(635.0f, 410.0f, 40.0f);
    spikes.emplace_back(780.0f, 180.0f, 40.0f);
    spikes.emplace_back(900.0f, 180.0f, 40.0f);

    keys.emplace_back(1050.0f, 50.0f);
    keys.emplace_back(840.0f, 180.0f);
    keys.emplace_back(350.0f, 175.0f);
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
            {
                if (gameOver || levelComplete)
                {
                    window.close();
                }
                else
                {
                    isPaused = !isPaused;
                    dartSpawner.restart();
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            break;
        default:
            break;
        }
    }
}

void Game::handleMouseClick(int x, int y)
{
    if (gameOver)
    {
        // Кнопка "Заново" (Рестарт) - позиция (350, 400), размер (200, 60)
        if (x >= 350 && x <= 550 && y >= 400 && y <= 460)
        {
            initializeLevel();
        }
        // Кнопка "Выйти" - позиция (650, 400), размер (200, 60)
        else if (x >= 650 && x <= 850 && y >= 400 && y <= 460)
        {
            window.close();
        }
    }
    else if (levelComplete)
    {
        // Кнопка "Снова" (Рестарт) - позиция (350, 450), размер (200, 60)
        if (x >= 350 && x <= 550 && y >= 450 && y <= 510)
        {
            initializeLevel();
        }
        // Кнопка "Выйти" - позиция (650, 450), размер (200, 60)
        else if (x >= 650 && x <= 850 && y >= 450 && y <= 510)
        {
            window.close();
        }
    }
    else if (isPaused)
    {
        // Кнопка "Продолжить" - позиция (200, 250), размер (180, 60)
        if (x >= 200 && x <= 380 && y >= 250 && y <= 310)
        {
            isPaused = false;
            dartSpawner.restart();
        }
        // Кнопка "Рестарт" - позиция (450, 250), размер (180, 60)
        else if (x >= 450 && x <= 630 && y >= 250 && y <= 310)
        {
            initializeLevel();
        }
        // Кнопка "Выйти" - позиция (700, 250), размер (180, 60)
        else if (x >= 700 && x <= 880 && y >= 250 && y <= 310)
        {
            window.close();
        }
    }
}

void Game::spawnDart()
{
    darts.emplace_back(1200.0f, 650.0f, -1.0f);
}

void Game::update()
{
    float deltaTime = gameClock.restart().asSeconds();

    // Если пауза, Game Over или Level Complete, не обновляем игру
    if (isPaused || gameOver || levelComplete)
        return;

    if (dartSpawner.getElapsedTime().asSeconds() >= DART_SPAWN_INTERVAL)
    {
        spawnDart();
        dartSpawner.restart();
    }

    // Обновляем таймер платформы с задержкой
    if (delayedPlatformActive && delayedPlatformTimer.getElapsedTime().asSeconds() >= DELAYED_PLATFORM_DURATION)
    {
        delayedGrounds.clear();
        delayedPlatformActive = false;
    }

    player.update(deltaTime);

    if (spawnedBox != nullptr)
    {
        spawnedBox->update(deltaTime);
    }

    for (auto& dart : darts)
    {
        dart.update(deltaTime);
    }

    checkCollisions();
}

void Game::checkCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();
    sf::FloatRect buttonBounds = button.getBounds();
    sf::FloatRect button2Bounds = button2.getBounds();
    sf::FloatRect button3Bounds = button3.getBounds();
    sf::FloatRect* spawnedBoxBounds = nullptr;

    if (spawnedBox != nullptr)
    {
        spawnedBoxBounds = new sf::FloatRect(spawnedBox->getBounds());
    }

    bool isPlayerColliding = false;

    // ==================== ПРОВЕРКА НАЖАТИЯ КНОПКИ 1 ====================
    bool playerOnButton = playerBounds.intersects(buttonBounds);
    if (spawnedBox != nullptr && spawnedBoxBounds != nullptr)
    {
        playerOnButton = playerOnButton || spawnedBoxBounds->intersects(buttonBounds);
    }

    if (playerOnButton && !buttonActivated)
    {
        button.press();
        buttonActivated = true;
        spawnedBox = new Box(1000.0f, 600.0f);
    }
    else if (!playerOnButton)
    {
        button.release();
    }

    // ==================== ПРОВЕРКА НАЖАТИЯ КНОПКИ 2 (ПЛАТФОРМЫ) ====================
    bool playerOnButton2 = playerBounds.intersects(button2Bounds);
    if (spawnedBox != nullptr && spawnedBoxBounds != nullptr)
    {
        playerOnButton2 = playerOnButton2 || spawnedBoxBounds->intersects(button2Bounds);
    }

    if (playerOnButton2)
    {
        button2.press();
        platformsActive = true;
    }
    else
    {
        button2.release();
        platformsActive = false;
    }

    // ==================== ПРОВЕРКА НАЖАТИЯ КНОПКИ 3 (ПЛАТФОРМА С ЗАДЕРЖКОЙ) ====================
    bool playerOnButton3 = playerBounds.intersects(button3Bounds);
    if (spawnedBox != nullptr && spawnedBoxBounds != nullptr)
    {
        playerOnButton3 = playerOnButton3 || spawnedBoxBounds->intersects(button3Bounds);
    }

    if (playerOnButton3)
    {
        button3.press();
        // Создаём платформу если её ещё нет
        if (delayedGrounds.empty() && !button3Pressed)
        {
            delayedGrounds.emplace_back(335.0f, 205.0f, 50.0f, 5.0f);
            delayedPlatformActive = true;
            delayedPlatformTimer.restart();
        }
        button3Pressed = true;
    }
    else
    {
        button3.release();
        button3Pressed = false;
    }

    // ==================== КОЛЛИЗИИ ПЕРСОНАЖА С ДРОТИКАМИ ====================
    playerBounds = player.getBounds();
    for (auto& dart : darts)
    {
        if (dart.getIsActive() && playerBounds.intersects(dart.getBounds()))
        {
            gameOver = true;
            return;
        }
    }

    // ==================== УНИЧТОЖЕНИЕ ДРОТИКОВ ====================
    for (auto& dart : darts)
    {
        if (!dart.getIsActive())
            continue;

        if (spawnedBox != nullptr)
        {
            sf::FloatRect spawnedBounds = spawnedBox->getBounds();
            if (spawnedBounds.intersects(dart.getBounds()))
            {
                dart.destroy();
                continue;
            }
        }

        for (int i = 0; i < spikes.size(); i++)
        {
            if (spikes[i].getBounds().intersects(dart.getBounds()))
            {
                dart.destroy();
                break;
            }
        }

        for (const auto& ground : grounds)
        {
            if (ground.getBounds().intersects(dart.getBounds()))
            {
                dart.destroy();
                break;
            }
        }

        if (platformsActive)
        {
            for (const auto& tempGround : temporaryGrounds)
            {
                if (tempGround.getBounds().intersects(dart.getBounds()))
                {
                    dart.destroy();
                    break;
                }
            }
        }

        if (delayedPlatformActive)
        {
            for (const auto& delayedGround : delayedGrounds)
            {
                if (delayedGround.getBounds().intersects(dart.getBounds()))
                {
                    dart.destroy();
                    break;
                }
            }
        }
    }

    // ==================== КОЛЛИЗИИ ПЕРСОНАЖА С ПЛАТФОРМАМИ ====================
    playerBounds = player.getBounds();
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

    // ==================== КОЛЛИЗИИ ПЕРСОНАЖА С ВРЕМЕННЫМИ ПЛАТФОРМАМИ ====================
    if (platformsActive && !isPlayerColliding)
    {
        playerBounds = player.getBounds();
        for (const auto& tempGround : temporaryGrounds)
        {
            sf::FloatRect groundBounds = tempGround.getBounds();

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
    }

    // ==================== КОЛЛИЗИИ ПЕРСОНАЖА С ПЛАТФОРМАМИ С ЗАДЕРЖКОЙ ====================
    if (delayedPlatformActive && !isPlayerColliding)
    {
        playerBounds = player.getBounds();
        for (const auto& delayedGround : delayedGrounds)
        {
            sf::FloatRect groundBounds = delayedGround.getBounds();

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
    }

    if (!isPlayerColliding)
        player.setOnGround(false);

    // ==================== КОЛЛИЗИИ СПАВНЕННОЙ КОРОБКИ С ПЛАТФОРМАМИ ====================
    if (spawnedBox != nullptr)
    {
        sf::FloatRect spawnedBounds = spawnedBox->getBounds();
        for (const auto& ground : grounds)
        {
            sf::FloatRect groundBounds = ground.getBounds();

            if (spawnedBounds.intersects(groundBounds))
            {
                float overlapLeft = (spawnedBounds.left + spawnedBounds.width) - groundBounds.left;
                float overlapRight = (groundBounds.left + groundBounds.width) - spawnedBounds.left;
                float overlapTop = (spawnedBounds.top + spawnedBounds.height) - groundBounds.top;
                float overlapBottom = (groundBounds.top + groundBounds.height) - spawnedBounds.top;

                float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                    std::min(overlapTop, overlapBottom));

                if (minOverlap == overlapTop &&
                    spawnedBounds.top + spawnedBounds.height / 2.0f < groundBounds.top)
                {
                    spawnedBox->stopVerticalVelocity();
                    spawnedBox->setPosition(spawnedBounds.left,
                        groundBounds.top - spawnedBounds.height);
                    spawnedBox->setOnGround(true);
                    continue;
                }
                else if (minOverlap == overlapBottom)
                {
                    spawnedBox->stopVerticalVelocity();
                    spawnedBox->setPosition(spawnedBounds.left,
                        groundBounds.top + groundBounds.height);
                    continue;
                }
                else if (minOverlap == overlapLeft)
                {
                    spawnedBox->stopHorizontalVelocity();
                    spawnedBox->setPosition(groundBounds.left - spawnedBounds.width,
                        spawnedBounds.top);
                    continue;
                }
                else if (minOverlap == overlapRight)
                {
                    spawnedBox->stopHorizontalVelocity();
                    spawnedBox->setPosition(groundBounds.left + groundBounds.width,
                        spawnedBounds.top);
                    continue;
                }
            }
        }

        // Коллизии со временными платформами
        if (platformsActive)
        {
            spawnedBounds = spawnedBox->getBounds();
            for (const auto& tempGround : temporaryGrounds)
            {
                sf::FloatRect groundBounds = tempGround.getBounds();

                if (spawnedBounds.intersects(groundBounds))
                {
                    float overlapLeft = (spawnedBounds.left + spawnedBounds.width) - groundBounds.left;
                    float overlapRight = (groundBounds.left + groundBounds.width) - spawnedBounds.left;
                    float overlapTop = (spawnedBounds.top + spawnedBounds.height) - groundBounds.top;
                    float overlapBottom = (groundBounds.top + groundBounds.height) - spawnedBounds.top;

                    float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                        std::min(overlapTop, overlapBottom));

                    if (minOverlap == overlapTop &&
                        spawnedBounds.top + spawnedBounds.height / 2.0f < groundBounds.top)
                    {
                        spawnedBox->stopVerticalVelocity();
                        spawnedBox->setPosition(spawnedBounds.left,
                            groundBounds.top - spawnedBounds.height);
                        spawnedBox->setOnGround(true);
                        continue;
                    }
                    else if (minOverlap == overlapBottom)
                    {
                        spawnedBox->stopVerticalVelocity();
                        spawnedBox->setPosition(spawnedBounds.left,
                            groundBounds.top + groundBounds.height);
                        continue;
                    }
                    else if (minOverlap == overlapLeft)
                    {
                        spawnedBox->stopHorizontalVelocity();
                        spawnedBox->setPosition(groundBounds.left - spawnedBounds.width,
                            spawnedBounds.top);
                        continue;
                    }
                    else if (minOverlap == overlapRight)
                    {
                        spawnedBox->stopHorizontalVelocity();
                        spawnedBox->setPosition(groundBounds.left + groundBounds.width,
                            spawnedBounds.top);
                        continue;
                    }
                }
            }
        }

        // Коллизии с платформами с задержкой
        if (delayedPlatformActive)
        {
            spawnedBounds = spawnedBox->getBounds();
            for (const auto& delayedGround : delayedGrounds)
            {
                sf::FloatRect groundBounds = delayedGround.getBounds();

                if (spawnedBounds.intersects(groundBounds))
                {
                    float overlapLeft = (spawnedBounds.left + spawnedBounds.width) - groundBounds.left;
                    float overlapRight = (groundBounds.left + groundBounds.width) - spawnedBounds.left;
                    float overlapTop = (spawnedBounds.top + spawnedBounds.height) - groundBounds.top;
                    float overlapBottom = (groundBounds.top + groundBounds.height) - spawnedBounds.top;

                    float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                        std::min(overlapTop, overlapBottom));

                    if (minOverlap == overlapTop &&
                        spawnedBounds.top + spawnedBounds.height / 2.0f < groundBounds.top)
                    {
                        spawnedBox->stopVerticalVelocity();
                        spawnedBox->setPosition(spawnedBounds.left,
                            groundBounds.top - spawnedBounds.height);
                        spawnedBox->setOnGround(true);
                        continue;
                    }
                    else if (minOverlap == overlapBottom)
                    {
                        spawnedBox->stopVerticalVelocity();
                        spawnedBox->setPosition(spawnedBounds.left,
                            groundBounds.top + groundBounds.height);
                        continue;
                    }
                    else if (minOverlap == overlapLeft)
                    {
                        spawnedBox->stopHorizontalVelocity();
                        spawnedBox->setPosition(groundBounds.left - spawnedBounds.width,
                            spawnedBounds.top);
                        continue;
                    }
                    else if (minOverlap == overlapRight)
                    {
                        spawnedBox->stopHorizontalVelocity();
                        spawnedBox->setPosition(groundBounds.left + groundBounds.width,
                            spawnedBounds.top);
                        continue;
                    }
                }
            }
        }

        spawnedBox->setOnGround(false);
    }

    // ==================== СТОЛКНОВЕНИЕ ПЕРСОНАЖА И СПАВНЕННОЙ КОРОБКИ ====================
    if (spawnedBox != nullptr)
    {
        playerBounds = player.getBounds();
        sf::FloatRect spawnedBounds = spawnedBox->getBounds();

        if (playerBounds.intersects(spawnedBounds))
        {
            float overlapLeft = (playerBounds.left + playerBounds.width) - spawnedBounds.left;
            float overlapRight = (spawnedBounds.left + spawnedBounds.width) - playerBounds.left;
            float overlapTop = (playerBounds.top + playerBounds.height) - spawnedBounds.top;
            float overlapBottom = (spawnedBounds.top + spawnedBounds.height) - playerBounds.top;

            float minOverlap = std::min(std::min(overlapLeft, overlapRight),
                std::min(overlapTop, overlapBottom));

            if (minOverlap == overlapTop &&
                playerBounds.top + playerBounds.height / 2.0f < spawnedBounds.top)
            {
                player.stopVerticalVelocity();
                player.setPosition(playerBounds.left,
                    spawnedBounds.top - playerBounds.height);
                player.setOnGround(true);
            }
            else if (minOverlap == overlapBottom)
            {
                player.stopVerticalVelocity();
            }
            else if (minOverlap == overlapLeft)
            {
                float boxSpeed = 300.0f;
                spawnedBox->setVelocity(boxSpeed, spawnedBox->getVelocity().y);
                player.stopHorizontalVelocity();
            }
            else if (minOverlap == overlapRight)
            {
                float boxSpeed = 300.0f;
                spawnedBox->setVelocity(-boxSpeed, spawnedBox->getVelocity().y);
                player.stopHorizontalVelocity();
            }
        }
        else
        {
            spawnedBox->setVelocity(0.0f, spawnedBox->getVelocity().y);
        }
    }

    // ==================== СТОЛКНОВЕНИЕ С ШИПАМИ ====================
    playerBounds = player.getBounds();
    for (int i = 0; i < spikes.size(); i++)
    {
        if (playerBounds.intersects(spikes[i].getBounds()))
        {
            gameOver = true;
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
    {
        levelComplete = true;
    }

    if (spawnedBoxBounds != nullptr)
    {
        delete spawnedBoxBounds;
        spawnedBoxBounds = nullptr;
    }
}

void Game::resetKeysAndDoor()
{
    keysCollected = 0;
    door.close();
    keys.clear();
    keys.emplace_back(1050.0f, 50.0f);
    keys.emplace_back(840.0f, 180.0f);
    keys.emplace_back(350.0f, 175.0f);
}

void Game::resetLevel()
{
    initializeLevel();
}

void Game::render()
{
    window.clear(sf::Color::Black);

    for (auto& ground : grounds)
        ground.draw(window);

    // Рисуем временные платформы если они активны
    if (platformsActive)
    {
        for (auto& tempGround : temporaryGrounds)
            tempGround.draw(window);
    }

    // Рисуем платформы с задержкой если они активны
    if (delayedPlatformActive)
    {
        for (auto& delayedGround : delayedGrounds)
            delayedGround.draw(window);
    }

    for (int i = 0; i < spikes.size(); i++)
    {
        spikes[i].draw(window);
    }

    for (auto& key : keys)
        key.draw(window);

    for (auto& dart : darts)
        dart.draw(window);

    button.draw(window);
    button2.draw(window);
    button3.draw(window);
    door.draw(window);

    if (spawnedBox != nullptr)
        spawnedBox->draw(window);

    player.draw(window);

    // Рисуем Game Over экран
    if (gameOver)
    {
        renderGameOver();
    }
    // Рисуем Level Complete экран
    else if (levelComplete)
    {
        renderLevelComplete();
    }
    // Рисуем Pause меню
    else if (isPaused)
    {
        renderPauseMenu();
    }

    window.display();
}

void Game::renderGameOver()
{
    // Полупрозрачный фон
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // Текст "GAME OVER"
    sf::Text gameOverText("GAME OVER", font, 80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setCharacterSize(80);
    gameOverText.setPosition(WINDOW_WIDTH / 2 - 280, 100);
    window.draw(gameOverText);

    // Кнопка "Заново"
    sf::RectangleShape restartButton(sf::Vector2f(200, 60));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(350, 400);
    window.draw(restartButton);

    sf::Text restartText("Zaново", font, 30);
    restartText.setFillColor(sf::Color::Black);
    restartText.setCharacterSize(30);
    restartText.setPosition(370, 408);
    window.draw(restartText);

    // Кнопка "Выйти"
    sf::RectangleShape exitButton(sf::Vector2f(200, 60));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(650, 400);
    window.draw(exitButton);

    sf::Text exitText("Vyjti", font, 30);
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(30);
    exitText.setPosition(680, 408);
    window.draw(exitText);
}

void Game::renderLevelComplete()
{
    // Полупрозрачный фон
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // Текст "LEVEL COMPLETE!"
    sf::Text completeText("LEVEL COMPLETE!", font, 80);
    completeText.setFillColor(sf::Color::Yellow);
    completeText.setCharacterSize(80);
    completeText.setPosition(WINDOW_WIDTH / 2 - 380, 100);
    window.draw(completeText);

    // Кнопка "Snova" (Снова)
    sf::RectangleShape restartButton(sf::Vector2f(200, 60));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(350, 450);
    window.draw(restartButton);

    sf::Text restartText("Snova", font, 30);
    restartText.setFillColor(sf::Color::Black);
    restartText.setCharacterSize(30);
    restartText.setPosition(375, 458);
    window.draw(restartText);

    // Кнопка "Vyjti" (Выйти)
    sf::RectangleShape exitButton(sf::Vector2f(200, 60));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(650, 450);
    window.draw(exitButton);

    sf::Text exitText("Vyjti", font, 30);
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(30);
    exitText.setPosition(680, 458);
    window.draw(exitText);
}

void Game::renderPauseMenu()
{
    // Полупрозрачный фон
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // Текст "PAUZA"
    sf::Text pauseText("PAUZA", font, 80);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setCharacterSize(80);
    pauseText.setPosition(WINDOW_WIDTH / 2 - 150, 80);
    window.draw(pauseText);

    // Кнопка "Prodolzhit'" (Продолжить)
    sf::RectangleShape continueButton(sf::Vector2f(180, 60));
    continueButton.setFillColor(sf::Color::Blue);
    continueButton.setPosition(200, 250);
    window.draw(continueButton);

    sf::Text continueText("Prodolzhit", font, 20);
    continueText.setFillColor(sf::Color::White);
    continueText.setCharacterSize(20);
    continueText.setPosition(210, 260);
    window.draw(continueText);

    // Кнопка "Restart"
    sf::RectangleShape restartButton(sf::Vector2f(180, 60));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(450, 250);
    window.draw(restartButton);

    sf::Text restartText("Restart", font, 20);
    restartText.setFillColor(sf::Color::Black);
    restartText.setCharacterSize(20);
    restartText.setPosition(470, 260);
    window.draw(restartText);

    // Кнопка "Vyjti" (Выйти)
    sf::RectangleShape exitButton(sf::Vector2f(180, 60));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(700, 250);
    window.draw(exitButton);

    sf::Text exitText("Vyjti", font, 20);
    exitText.setFillColor(sf::Color::White);
    exitText.setCharacterSize(20);
    exitText.setPosition(730, 260);
    window.draw(exitText);
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