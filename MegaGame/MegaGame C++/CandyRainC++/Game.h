#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>
#include "FallingObject.h"
#include "Sweet.h"
#include "Trash.h"
#include "Heart.h"
#include "Player.h"

enum class GameState {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    SHOW_RECORDS
};

class Game {
private:
    sf::RenderWindow window;
    sf::Texture backgroundTex, candyTex, donutTex, lollipopTex, cakeTex, trashTex, heartTex, playerTex;
    sf::Sprite background;

    std::vector<std::unique_ptr<FallingObject>> fallingObjects;
    std::unique_ptr<Player> player;

    int score;
    int health;
    float spawnTimer;
    float spawnInterval;

    sf::Font font;
    sf::Text scoreText, healthText, gameOverText;
    sf::Text timerText, targetText, pauseText, recordsText;
    sf::Text restartHintText;


    bool gameOver;
    bool goalAchieved;

    std::mt19937 rng;

    GameState state;

    // цели
    int targetCandy;
    int targetDonut;
    int targetLollipop;
    int collectedCandy;
    int collectedDonut;
    int collectedLollipop;

    // таймер
    float elapsedTime;
    std::vector<float> records;

    void loadTextures();
    void spawnObject();
    void checkCollisions();
    void updateUI();
    void resetGame();
    float getRandomFallSpeed();
    void generateTargets();
    void loadRecords();
    void saveRecord(float timeSeconds);
    void updateTimer(float deltaTime);
    void updateTargetsUI();
    void showRecordsText();

public:
    Game();
    ~Game();

    void run();
    void update(float deltaTime);
    void render();
    void handleInput();
};
