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
    const std::string& background;
    std::string gamestatus;
public:
    static const int floorY = 5;
    static const int maxfloorY = 20;
    static const int maxfloorX = 40;
    static const int maxspeed = 5;
    static const int playersize = 10;
    static const int countchange = 1;
    GameMain(int h, const std::string & bg, std::string status );
    ~GameMain();
    void Start();
    void ChangeStatus();
    bool WinCheck(int countcandy, int countcake, int countdonut);
    bool LoseCheck();
    void DisplayInfo() const;
};

