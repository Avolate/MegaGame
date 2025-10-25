#pragma once
#include <string>
#include "Player.h"
#include "Sweets_distribution.h"
#include "Sweet.h"
#include "Trash.h"
class GameMain
{
private:
    int health;
  /*  int candycount;
    int cakecount;
    int donutcount;
    int trashcount;*/
    const std::string& background;
    std::string game_status;
public:
    static const int floorY = 5;
    static const int maxfloorY = 20;
    static const int maxfloorX = 40;
    static const int maxspeed = 5;
    GameMain(int h, const std::string & bg, std::string status );
    ~GameMain();
    void start();
    void changeStatus();
    bool winCheck(int count_candy, int count_cake, int count_donut);
    bool loseCheck();
    void displayInfo() const;
};

