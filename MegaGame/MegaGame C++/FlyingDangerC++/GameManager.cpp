#include "GameManager.h"
#include <sstream>

GameManager::GameManager()
    : window(sf::VideoMode(800, 600), "Flying Danger"),
    currentState(GameState::PLAYING),
    destroyedBoulders(0),
    archerHealth(3),
    castleHealth(3),
    archer(nullptr),
    castle(nullptr),
    bossBoulder(nullptr),
    spawnInterval(1.5f),
    bouldersOnScreen(0)
{
    srand(static_cast<unsigned>(time(0)));
    window.setFramerateLimit(60);

    // Инициализация игровых объектов
    archer = new Archer();
    castle = new Castle();

    // Пробуем загрузить шрифт (если нет, игра всё равно работает без HUD)
    font.loadFromFile("Arial.ttf");
}

GameManager::~GameManager()
{
    delete archer;
    delete castle;
    if (bossBoulder) delete bossBoulder;

    for (auto b : boulders) delete b;
    for (auto p : projectiles) delete p;
    for (auto h : healthPotions) delete h;
}

void GameManager::run()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        handleInput();
        update(deltaTime);
        render();
    }
}

void GameManager::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
}

void GameManager::update(float deltaTime)
{
    if (currentState != GameState::PLAYING)
        return;

    // Обновление archer'а
    archer->update(deltaTime);

    // Спавнинг булыжников
    if (spawnTimer.getElapsedTime().asSeconds() > spawnInterval && bouldersOnScreen < 3)
    {
        spawnBoulder();
        spawnTimer.restart();
        spawnInterval = 1.0f + (rand() % 15) / 10.0f;  // 1.0 - 2.5 сек
    }

    // Обновление булыжников
    for (auto b : boulders)
    {
        b->update(deltaTime);
    }

    // Обновление пуль
    for (auto p : projectiles)
    {
        p->update(deltaTime);
    }

    // Обновление зелий
    for (auto h : healthPotions)
    {
        h->update(deltaTime);
    }

    // Обновление босса
    if (bossBoulder)
    {
        bossBoulder->update(deltaTime);
    }
}

void GameManager::spawnBoulder()
{
    Boulder* newBoulder = new Boulder();
    boulders.push_back(newBoulder);
    bouldersOnScreen++;
}

void GameManager::render()
{
    window.clear(sf::Color::Black);

    // Отрисовка замка
    castle->draw(window);

    // Отрисовка булыжников
    for (auto b : boulders)
    {
        b->draw(window);
    }

    // Отрисовка пуль
    for (auto p : projectiles)
    {
        p->draw(window);
    }

    // Отрисовка зелий
    for (auto h : healthPotions)
    {
        h->draw(window);
    }

    // Отрисовка archer'а (последним, чтобы был сверху)
    archer->draw(window);

    // Отрисовка босса
    if (bossBoulder)
    {
        bossBoulder->draw(window);
    }

    // Отрисовка HUD
    drawHUD();

    window.display();
}

void GameManager::drawHUD()
{
    // Простой HUD без шрифта 
    sf::RectangleShape hudBg(sf::Vector2f(800, 50));
    hudBg.setFillColor(sf::Color(50, 50, 50, 200));
    window.draw(hudBg);

    // Текст счётчика 
    if (font.getInfo().family != "")
    {
        sf::Text destroyedText("Destroyed: " + std::to_string(destroyedBoulders), font, 20);
        destroyedText.setPosition(20, 15);
        destroyedText.setFillColor(sf::Color::White);
        window.draw(destroyedText);

        sf::Text healthText("Health: " + std::to_string(archerHealth), font, 20);
        healthText.setPosition(300, 15);
        healthText.setFillColor(sf::Color::Green);
        window.draw(healthText);

        sf::Text castleText("Castle HP: " + std::to_string(castleHealth), font, 20);
        castleText.setPosition(550, 15);
        castleText.setFillColor(sf::Color::Cyan);
        window.draw(castleText);
    }
}
