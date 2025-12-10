#include "Game.h"
#include <iostream>

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 1000;
const float SPAWN_INTERVAL = 0.8f;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Candy Rain"),
    score(0), health(5), spawnTimer(0), spawnInterval(SPAWN_INTERVAL),
    gameOver(false), rng(std::random_device{}()) {
    window.setFramerateLimit(60);

    loadTextures();

    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 50,
        WINDOW_HEIGHT - 180, 600.0f, health, playerTex);

    // Пробуем несколько путей к шрифту
    bool fontLoaded = false;

    if (font.loadFromFile("assets/arial.ttf")) {
        fontLoaded = true;
        std::cout << "Font loaded from assets/arial.ttf" << std::endl;
    }
    else if (font.loadFromFile("arial.ttf")) {
        fontLoaded = true;
        std::cout << "Font loaded from arial.ttf" << std::endl;
    }
    else if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        fontLoaded = true;
        std::cout << "Font loaded from C:/Windows/Fonts/arial.ttf" << std::endl;
    }
    else {
        std::cerr << "Error: Could not load font from any path!" << std::endl;
        std::cerr << "Tried: assets/arial.ttf, arial.ttf, C:/Windows/Fonts/arial.ttf" << std::endl;
    }

    if (fontLoaded) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(52);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setOutlineThickness(2.5f);
        scoreText.setOutlineColor(sf::Color::Black);
        scoreText.setPosition(30, 30);

        healthText.setFont(font);
        healthText.setCharacterSize(52);
        healthText.setFillColor(sf::Color::Red);
        healthText.setOutlineThickness(2.5f);
        healthText.setOutlineColor(sf::Color::Black);
        healthText.setPosition(30, 110);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(120);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOutlineThickness(5.f);
        gameOverText.setOutlineColor(sf::Color::White);
        gameOverText.setPosition(WINDOW_WIDTH / 2 - 450, WINDOW_HEIGHT / 2 - 150);
        gameOverText.setString("GAME OVER!");
    }
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

float Game::getRandomFallSpeed() {
    // Рандомная скорость падения от 150 до 350 пикселей в секунду
    std::uniform_real_distribution<> speedDist(150.0, 350.0);
    return static_cast<float>(speedDist(rng));
}

void Game::spawnObject() {
    std::uniform_int_distribution<> xDist(60, WINDOW_WIDTH - 180);
    std::uniform_int_distribution<> typeDist(0, 10);

    int x = xDist(rng);
    int type = typeDist(rng);
    float randomSpeed = getRandomFallSpeed();

    if (type < 6) {
        // Сладости (60% шанс)
        fallingObjects.push_back(std::make_unique<Sweet>(
            static_cast<float>(x), -150, randomSpeed, candyTex, donutTex, lollipopTex, cakeTex
        ));
    }
    else if (type < 9) {
        // Мусор (30% шанс)
        fallingObjects.push_back(std::make_unique<Trash>(
            static_cast<float>(x), -200, randomSpeed, trashTex
        ));
    }
    else {
        // Сердца (10% шанс)
        fallingObjects.push_back(std::make_unique<Heart>(
            static_cast<float>(x), -150, randomSpeed, heartTex
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
    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 50,
        WINDOW_HEIGHT - 180, 600.0f, 5, playerTex);
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
