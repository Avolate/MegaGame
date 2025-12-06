#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Ground.h"

class Game
{
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Ground> grounds;
    sf::Clock gameClock;

    // Параметры окна
    const float WINDOW_WIDTH = 1200.0f;
    const float WINDOW_HEIGHT = 800.0f;

public:
    Game();

    void initializeLevel();
    void handleEvents();
    void update();
    void render();
    void checkCollisions();

    void run();
    bool isRunning() const;
};