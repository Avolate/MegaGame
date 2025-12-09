#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "FallingObject.h"

class Game {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<FallingObject>> fallingObjects;
    int score;
    int health;

public:
    Game();
    ~Game();

    void run();
    void update(float deltaTime);
    void render();
    void handleInput();
};

#endif
