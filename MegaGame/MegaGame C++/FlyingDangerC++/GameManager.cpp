#include "GameManager.h"

GameManager::GameManager()
    : window(sf::VideoMode(800, 600), "Flying Danger"),
    currentState(GameState::PLAYING),
    destroyedBoulders(0),
    archerHealth(3),
    castleHealth(3),
    archer(nullptr),
    castle(nullptr),
    bossBoulder(nullptr)
{
    window.setFramerateLimit(60);

    // Инициализация игровых объектов
    archer = new Archer();
    castle = new Castle();
}

GameManager::~GameManager()
{
    delete archer;
    delete castle;
    delete bossBoulder;

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
    // TODO: реализовать логику обновления
}

void GameManager::render()
{
    window.clear(sf::Color::Black);

    // TODO: отрисовка объектов

    window.display();
}
