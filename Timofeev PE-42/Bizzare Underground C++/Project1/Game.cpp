#include "Game.h"
#include <iostream>

Game::Game() : background("DefaultBG"), exitX(100), exitY(100) {
    std::cout << "--- MainGame Initialized ---" << std::endl;
    std::cout << "  Background: '" << getBackground() << "'" << std::endl;
    std::cout << "  Exit Position: (" << getExitX() << ", " << getExitY() << ")" << std::endl;
}

Game::~Game() {
    std::cout << "--- MainGame Destroyed ---" << std::endl;
}

void Game::startGame(bool isAlive) {
    std::cout << "MainGame::startGame() called. Player initial state: " << (isAlive ? "Alive" : "Dead") << std::endl;
}

bool Game::win(int characterPositionX, int characterPositionY) {
    std::cout << "MainGame::win() called. Checking condition at Character(" << characterPositionX << ", " << characterPositionY << ")." << std::endl;
    if (characterPositionX == getExitX() && characterPositionY == getExitY()) {
        std::cout << "MainGame::win(): Victory!." << std::endl;
        return true;
    }
    std::cout << "MainGame::win(): Not yet." << std::endl;
    return false;
}

// Getters
std::string Game::getBackground() const { return background; }
int Game::getExitX() const { return exitX; }
int Game::getExitY() const { return exitY; }

// Setters
void Game::setBackground(const std::string& bg) {
    background = bg;
    std::cout << "MainGame::setBackground() called. New background: '" << background << "'" << std::endl;
}
void Game::setExitX(int x) {
    exitX = x;
    std::cout << "MainGame::setExitX() called. New exitX: " << exitX << std::endl;
}
void Game::setExitY(int y) {
    exitY = y;
    std::cout << "MainGame::setExitY() called. New exitY: " << exitY << std::endl;
}