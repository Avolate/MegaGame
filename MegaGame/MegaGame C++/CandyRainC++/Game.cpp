#include "Game.h"
#include <iostream>

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 800;
const float SPAWN_INTERVAL = 0.8f;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Candy Rain"),
    score(0), health(5), spawnTimer(0), spawnInterval(SPAWN_INTERVAL),
    gameOver(false), rng(std::random_device{}()) {
    window.setFramerateLimit(60);

    loadTextures();

    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 40,
        WINDOW_HEIGHT - 150, 500.0f, health, playerTex);

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20);

    healthText.setFont(font);
    healthText.setCharacterSize(28);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition(20, 60);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(WINDOW_WIDTH / 2 - 250, WINDOW_HEIGHT / 2 - 100);
    gameOverText.setString("GAME OVER!");
}

Game::~Game() {
}

void Game::loadTextures() {
    if (!backgroundTex.loadFromFile("assets/background.png")) {
        std::cerr << "Error loading background!" << std::endl;
    }
    if (!candyTex.loadFromFile("assets/candy.png")) {
        std::cerr << "Error loading candy!" << std::endl;
    }
    if (!donutTex.loadFromFile("assets/donut.png")) {
        std::cerr << "Error loading donut!" << std::endl;
    }
    if (!lollipopTex.loadFromFile("assets/lollipop.png")) {
        std::cerr << "Error loading lollipop!" << std::endl;
    }
    if (!cakeTex.loadFromFile("assets/cake.png")) {
        std::cerr << "Error loading cake!" << std::endl;
    }
    if (!trashTex.loadFromFile("assets/trash.png")) {
        std::cerr << "Error loading trash!" << std::endl;
    }
    if (!heartTex.loadFromFile("assets/heart.png")) {
        std::cerr << "Error loading heart!" << std::endl;
    }
    if (!playerTex.loadFromFile("assets/player.png")) {
        std::cerr << "Error loading player!" << std::endl;
    }

    background.setTexture(backgroundTex);
    background.setScale(static_cast<float>(WINDOW_WIDTH) / 320.0f,
        static_cast<float>(WINDOW_HEIGHT) / 183.0f);
}

void Game::spawnObject() {
    std::uniform_int_distribution<> xDist(50, WINDOW_WIDTH - 150);
    std::uniform_int_distribution<> typeDist(0, 10);

    int x = xDist(rng);
    int type = typeDist(rng);

    if (type < 6) {
        // Сладости (60% шанс)
        fallingObjects.push_back(std::make_unique<Sweet>(
            static_cast<float>(x), -100, 200.0f, candyTex, donutTex, lollipopTex, cakeTex
        ));
    }
    else if (type < 9) {
        // Мусор (30% шанс)
        fallingObjects.push_back(std::make_unique<Trash>(
            static_cast<float>(x), -150, 250.0f, trashTex
        ));
    }
    else {
        // Сердца (10% шанс)
        fallingObjects.push_back(std::make_unique<Heart>(
            static_cast<float>(x), -100, 180.0f, heartTex
        ));
    }
}

void Game::checkCollisions() {
    sf::FloatRect playerBounds = player->getBounds();

    for (auto it = fallingObjects.begin(); it != fallingObjects.end(); ) {
        sf::FloatRect objBounds = (*it)->getBounds();

        if (playerBounds.intersects(objBounds)) {
            if (Sweet* sweet = dynamic_cast<Sweet*>(it->get())) {
                score += sweet->getPoints();
                (*it)->setActive(false);
            }
            else if (Trash* trash = dynamic_cast<Trash*>(it->get())) {
                player->takeDamage(trash->getDamage());
                (*it)->setActive(false);
            }
            else if (Heart* heart = dynamic_cast<Heart*>(it->get())) {
                player->heal(heart->getHealthRestore());
                (*it)->setActive(false);
            }
        }

        if (objBounds.top > WINDOW_HEIGHT || !(*it)->getActive()) {
            it = fallingObjects.erase(it);
        }
        else {
            ++it;
        }
    }

    if (player->getHealth() <= 0) {
        gameOver = true;
    }
}

void Game::updateUI() {
    scoreText.setString("Score: " + std::to_string(score));
    healthText.setString("Health: " + std::to_string(player->getHealth()) +
        "/" + std::to_string(player->getMaxHealth()));
}

void Game::resetGame() {
    score = 0;
    gameOver = false;
    fallingObjects.clear();
    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 40,
        WINDOW_HEIGHT - 150, 500.0f, 5, playerTex);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleInput();
        if (!gameOver) {
            update(deltaTime);
        }
        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R && gameOver) {
                resetGame();
            }
        }
    }
}

void Game::update(float deltaTime) {
    player->update(deltaTime, WINDOW_WIDTH);

    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnObject();
        spawnTimer = 0;
    }

    for (auto& obj : fallingObjects) {
        if (obj) {
            obj->update(deltaTime);
        }
    }

    checkCollisions();
    updateUI();
}

void Game::render() {
    window.clear(sf::Color::Black);

    window.draw(background);

    for (auto& obj : fallingObjects) {
        if (obj) {
            obj->draw(window);
        }
    }

    player->draw(window);

    window.draw(scoreText);
    window.draw(healthText);

    if (gameOver) {
        window.draw(gameOverText);
    }

    window.display();
}
