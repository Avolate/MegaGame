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

    bool gameOver;
    std::mt19937 rng;

    void loadTextures();
    void spawnObject();
    void checkCollisions();
    void updateUI();
    void resetGame();
    float getRandomFallSpeed();

public:
    Game();
    ~Game();

    void run();
    void update(float deltaTime);
    void render();
    void handleInput();
};
