#include "Game.h"
#include <iostream>
#include <fstream>
#include <cstdio>

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 1000;
const float SPAWN_INTERVAL = 0.5f;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Candy Rain", sf::Style::Titlebar | sf::Style::Close),
    score(0), health(5), spawnTimer(0), spawnInterval(SPAWN_INTERVAL),
    gameOver(false), rng(std::random_device{}()),
    state(GameState::MAIN_MENU),
    targetCandy(0), targetDonut(0), targetLollipop(0),
    collectedCandy(0), collectedDonut(0), collectedLollipop(0),
    elapsedTime(0.0f),
    goalAchieved(false) {
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
        // Текст таймера
        timerText.setFont(font);
        timerText.setCharacterSize(48);
        timerText.setFillColor(sf::Color::Cyan);
        timerText.setOutlineThickness(2.f);
        timerText.setOutlineColor(sf::Color::Black);
        timerText.setPosition(WINDOW_WIDTH - 420.f, 30.f);

        // Текст цели
        targetText.setFont(font);
        targetText.setCharacterSize(32);
        targetText.setFillColor(sf::Color::White);
        targetText.setOutlineThickness(2.f);
        targetText.setOutlineColor(sf::Color::Black);
        targetText.setPosition(30.f, 190.f);

        // Текст паузы
        pauseText.setFont(font);
        pauseText.setCharacterSize(56);
        pauseText.setFillColor(sf::Color::Yellow);
        pauseText.setOutlineThickness(3.f);
        pauseText.setOutlineColor(sf::Color::Black);
        pauseText.setString(
            "PAUSED\n\n"
            "R - Restart\n"
            "C - Continue\n"
            "T - Records\n"
            "M - Main Menu"
        );
        pauseText.setPosition(WINDOW_WIDTH / 2.f - 260.f, WINDOW_HEIGHT / 2.f - 200.f);

        // Текст рекордов
        recordsText.setFont(font);
        recordsText.setCharacterSize(40);
        recordsText.setFillColor(sf::Color::White);
        recordsText.setOutlineThickness(2.f);
        recordsText.setOutlineColor(sf::Color::Black);
        recordsText.setPosition(100.f, 120.f);

        // Текст здоровья
        healthText.setFont(font);
        healthText.setCharacterSize(48);
        healthText.setFillColor(sf::Color::Red);
        healthText.setOutlineThickness(2.5f);
        healthText.setOutlineColor(sf::Color::Black);
        healthText.setPosition(30.f, 100.f);

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(120);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOutlineThickness(5.f);
        gameOverText.setOutlineColor(sf::Color::White);
        gameOverText.setPosition(WINDOW_WIDTH / 2 - 450, WINDOW_HEIGHT / 2 - 150);
        gameOverText.setString("WIN!");

        restartHintText.setFont(font);
        restartHintText.setCharacterSize(40);
        restartHintText.setFillColor(sf::Color::White);
        restartHintText.setOutlineThickness(2.f);
        restartHintText.setOutlineColor(sf::Color::Black);
        restartHintText.setString("Press R to restart");
        restartHintText.setPosition(
            WINDOW_WIDTH / 2.f - 200.f,
            WINDOW_HEIGHT / 2.f + 20.f
        );

    }

    loadRecords();
    generateTargets();
    updateTargetsUI();
    updateTimer(0.f);
}

Game::~Game() {
}

void Game::loadTextures() {
    if (!backgroundTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/background.png")) {
        std::cerr << "Error loading background!" << std::endl;
    }
    if (!candyTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/candy.png")) {
        std::cerr << "Error loading candy!" << std::endl;
    }
    if (!donutTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/donut.png")) {
        std::cerr << "Error loading donut!" << std::endl;
    }
    if (!lollipopTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/lollipop.png")) {
        std::cerr << "Error loading lollipop!" << std::endl;
    }
    if (!cakeTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/cake.png")) {
        std::cerr << "Error loading cake!" << std::endl;
    }
    if (!trashTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/trash.png")) {
        std::cerr << "Error loading trash!" << std::endl;
    }
    if (!heartTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/heart.png")) {
        std::cerr << "Error loading heart!" << std::endl;
    }
    if (!playerTex.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\CandyRainC++\\assets/player.png")) {
        std::cerr << "Error loading player!" << std::endl;
    }

    background.setTexture(backgroundTex);
    background.setScale(static_cast<float>(WINDOW_WIDTH) / 2230.0f,
        static_cast<float>(WINDOW_HEIGHT) / 1275.0f);
}

float Game::getRandomFallSpeed() {
    std::uniform_real_distribution<> speedDist(150.0, 350.0);
    return static_cast<float>(speedDist(rng));
}

void Game::generateTargets() {
    int total = 30;

    std::uniform_int_distribution<> d1(5, 15);
    std::uniform_int_distribution<> d2(5, 15);

    targetCandy = d1(rng);
    targetDonut = d2(rng);

    if (targetCandy + targetDonut > total - 5) {
        targetDonut = total - 5 - targetCandy;
    }
    if (targetDonut < 0) targetDonut = 0;

    targetLollipop = total - targetCandy - targetDonut;

    collectedCandy = collectedDonut = collectedLollipop = 0;
}

void Game::updateTargetsUI() {
    targetText.setString(
        "Goal (total 30 sweets):\n"
        "Candy:    " + std::to_string(collectedCandy) + "/" + std::to_string(targetCandy) + "\n" +
        "Donut:    " + std::to_string(collectedDonut) + "/" + std::to_string(targetDonut) + "\n" +
        "Lollipop: " + std::to_string(collectedLollipop) + "/" + std::to_string(targetLollipop)
    );
}

void Game::updateTimer(float deltaTime) {
    if (state == GameState::PLAYING) {
        elapsedTime += deltaTime;
    }

    int seconds = static_cast<int>(elapsedTime);
    int minutes = seconds / 60;
    seconds %= 60;

    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "Time: %02d:%02d", minutes, seconds);
    timerText.setString(buffer);
}

void Game::loadRecords() {
    records.clear();
    std::ifstream in("records.txt");
    if (!in.is_open()) return;

    float t;
    while (in >> t) {
        records.push_back(t);
    }
    in.close();
}

void Game::saveRecord(float timeSeconds) {
    records.push_back(timeSeconds);
    std::ofstream out("records.txt", std::ios::trunc);
    if (!out.is_open()) return;

    for (float r : records) {
        out << r << "\n";
    }
    out.close();
}

void Game::showRecordsText() {
    std::string text = "Records (best times in seconds):\n\n";
    if (records.empty()) {
        text += "No records yet.\n";
    }
    else {
        for (size_t i = 0; i < records.size(); ++i) {
            int sec = static_cast<int>(records[i]);
            int min = sec / 60;
            sec %= 60;
            char buffer[64];
            std::snprintf(buffer, sizeof(buffer), "%zu) %02d:%02d\n", i + 1, min, sec);
            text += buffer;
        }
    }
    text += "\nM - Main menu";
    recordsText.setString(text);
}

void Game::spawnObject() {
    std::uniform_int_distribution<> xDist(60, WINDOW_WIDTH - 180);
    std::uniform_int_distribution<> typeDist(0, 19);

    int x = xDist(rng);
    int type = typeDist(rng);
    float randomSpeed = getRandomFallSpeed();

    if (type < 12) {
        fallingObjects.push_back(std::make_unique<Sweet>(
            static_cast<float>(x), -150, randomSpeed, candyTex, donutTex, lollipopTex, cakeTex
        ));
    }
    else if (type < 19) {
        fallingObjects.push_back(std::make_unique<Trash>(
            static_cast<float>(x), -200, randomSpeed, trashTex
        ));
    }
    else {
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
                switch (sweet->getType()) {
                case SweetType::CANDY:
                    if (collectedCandy < targetCandy) collectedCandy++;
                    break;
                case SweetType::DONUT:
                    if (collectedDonut < targetDonut) collectedDonut++;
                    break;
                case SweetType::LOLLIPOP:
                    if (collectedLollipop < targetLollipop) collectedLollipop++;
                    break;
                default:
                    break;
                }
                (*it)->setActive(false);
                updateTargetsUI();
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

    // Проверка выполнения цели
    bool goalReached =
        collectedCandy >= targetCandy &&
        collectedDonut >= targetDonut &&
        collectedLollipop >= targetLollipop;

    if (goalReached && state == GameState::PLAYING) {
        gameOver = true;
        state = GameState::GAME_OVER;
        goalAchieved = true;
        saveRecord(elapsedTime);
        showRecordsText();
        gameOverText.setString("WIN!");
        // restartHintText.setString("Press R to restart");
    }

    if (player->getHealth() <= 0 && state == GameState::PLAYING) {
        gameOver = true;
        state = GameState::GAME_OVER;
        goalAchieved = false;
        gameOverText.setString("GAME OVER!");
        // restartHintText.setString("Press R to restart");
    }

}

void Game::updateUI() {
    healthText.setString("Health: " + std::to_string(player->getHealth()) +
        "/" + std::to_string(player->getMaxHealth()));
}

void Game::resetGame() {
    score = 0;
    gameOver = false;
    goalAchieved = false;
    fallingObjects.clear();
    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f - 50,
        WINDOW_HEIGHT - 180, 600.0f, 5, playerTex);
    elapsedTime = 0.f;
    generateTargets();
    updateTargetsUI();
    updateTimer(0.f);
    health = 5;
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

        if (event.type == sf::Event::KeyPressed) {
            if (state == GameState::PLAYING) {
                if (event.key.code == sf::Keyboard::Escape) {
                    state = GameState::PAUSED;
                }
            }
            else if (state == GameState::PAUSED) {
                if (event.key.code == sf::Keyboard::R) {
                    resetGame();
                    state = GameState::PLAYING;
                }
                else if (event.key.code == sf::Keyboard::C) {
                    state = GameState::PLAYING;
                }
                else if (event.key.code == sf::Keyboard::T) {
                    showRecordsText();  // <-- добавь это
                    state = GameState::SHOW_RECORDS;
                }
                else if (event.key.code == sf::Keyboard::M) {
                    state = GameState::MAIN_MENU;
                }
            }
            else if (state == GameState::GAME_OVER) {
                if (event.key.code == sf::Keyboard::R) {
                    resetGame();
                    state = GameState::PLAYING;
                }
                else if (event.key.code == sf::Keyboard::M) {
                    state = GameState::MAIN_MENU;
                }
                else if (event.key.code == sf::Keyboard::T) {
                    showRecordsText();  
                    state = GameState::SHOW_RECORDS;
                }
            }
            else if (state == GameState::MAIN_MENU) {
                if (event.key.code == sf::Keyboard::Enter ||
                    event.key.code == sf::Keyboard::Space) {
                    resetGame();
                    state = GameState::PLAYING;
                }
            }
            else if (state == GameState::SHOW_RECORDS) {
                if (event.key.code == sf::Keyboard::M) {
                    state = GameState::MAIN_MENU;
                }
            }
        }
    }
}


void Game::update(float deltaTime) {
    if (state != GameState::PLAYING) {
        updateTimer(0.f);
        return;
    }

    updateTimer(deltaTime);
    player->update(deltaTime, WINDOW_WIDTH);

    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        if (rand() % 100 < 100) {      // доп. 30% шанс второго объекта
            spawnObject();
        }
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

    if (state == GameState::MAIN_MENU) {
        window.draw(background);

        sf::Text title("Candy Rain", font, 96);
        title.setFillColor(sf::Color::Magenta);
        title.setOutlineThickness(4.f);
        title.setOutlineColor(sf::Color::Black);
        title.setPosition(WINDOW_WIDTH / 2.f - 260.f, 150.f);

        sf::Text press("Press ENTER or SPACE to start", font, 40);
        press.setFillColor(sf::Color::White);
        press.setOutlineThickness(2.f);
        press.setOutlineColor(sf::Color::Black);
        press.setPosition(WINDOW_WIDTH / 2.f - 340.f, 400.f);

        window.draw(title);
        window.draw(press);
    }
    else if (state == GameState::SHOW_RECORDS) {
        window.draw(background);
        window.draw(recordsText);
    }
    else {
        window.draw(background);

        for (auto& obj : fallingObjects) {
            if (obj) {
                obj->draw(window);
            }
        }
        player->draw(window);

        window.draw(timerText);
        window.draw(healthText);
        window.draw(targetText);

        if (state == GameState::PAUSED) {
            window.draw(pauseText);
        }
        else if (state == GameState::GAME_OVER) {
            window.draw(gameOverText);
            window.draw(restartHintText);
        }
    }

    window.display();
}
