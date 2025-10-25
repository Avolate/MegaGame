#pragma once
#include "FallingObject.h"
#include "Player.h"
class Heart :
    public FallingObject
{
public:
    Heart(int x, int y, std::string spr, int spd, int num, bool p_touch, bool f_touch);
    ~Heart();

    void playerCatchHeart(int playerX, int playerY);
    void plusHealth(int& health);

};

