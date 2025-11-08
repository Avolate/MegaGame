#pragma once
#include <string>

class Game {
private:
    std::string background;
    int exitX;
    int exitY;

public:
    Game();
    ~Game();

    void startGame(bool isAlive);
    bool win(int characterPositionX, int characterPositionY);

    // Getters
    std::string getBackground() const;
    int getExitX() const;
    int getExitY() const;

    // Setters
    void setBackground(const std::string& bg);
    void setExitX(int x);
    void setExitY(int y);
};
 