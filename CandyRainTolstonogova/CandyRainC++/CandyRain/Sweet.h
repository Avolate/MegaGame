#pragma once
#include "FallingObject.h"
#include "GameMain.h"
#include "Player.h"
class Sweet :
    public FallingObject
{
public:
    Sweet(int x, int y,  std::string spr, int spd, int num, bool p_touch, bool f_touch);
    ~Sweet();
    void playerCatchSweet(int playerX, int playerY);
    void sweetTouchFloor();
    void changeCandy(int &count_candy);
    void changeCake(int &count_cake);
    void changeDonut(int &count_donut);
};

