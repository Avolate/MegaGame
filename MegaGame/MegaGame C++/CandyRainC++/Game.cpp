#include "Game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Candy Rain"),
    score(0), health(5) {
    window.setFramerateLimit(60);
}

Game::~Game() {
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleInput();
        update(deltaTime);
        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    // Обновление всех падающих объектов
    for (auto& obj : fallingObjects) {
        if (obj) {
            obj->update(deltaTime);
        }
    }

    // Удаление неактивных объектов
    fallingObjects.erase(
        std::remove_if(fallingObjects.begin(), fallingObjects.end(),
            [](const std::unique_ptr<FallingObject>& obj) {
                return !obj->getActive();
            }),
        fallingObjects.end()
    );
}

void Game::render() {
    window.clear(sf::Color::White);

    // Отрисовка всех объектов
    for (auto& obj : fallingObjects) {
        if (obj) {
            obj->draw(window);
        }
    }

    window.display();
}
