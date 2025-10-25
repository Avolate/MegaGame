#pragma once
#include "FallingObject.h"
#include "Player.h"
class Heart :
    public FallingObject
{
public:
    Heart(int x, int y, std::string spr, int spd, int num, bool ptouch, bool ftouch);
    ~Heart();

    void PlayerCatchHeart(int playerX, int playerY);
    void PlusHealth(int& health);

};

