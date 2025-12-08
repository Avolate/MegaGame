#pragma once
#include <C:\Users\olegb\OneDrive\Documents\BizzareUnderground\BizzareUnderground\SFML-include\SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Spike.h"
#include "Key.h"
#include "Door.h"

class Game
{
private:
    sf::RenderWindow window;
    Player player;
    std::vector<Ground> grounds;
    std::vector<Spike> spikes;
    std::vector<Key> keys;
    Door door;

    int keysCollected;  // Количество собранных ключей

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
    void resetLevel();

    void run();
    bool isRunning() const;
};