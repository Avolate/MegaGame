#pragma once
#include "FallingObject.h"
#include "Player.h"
class Trash :
    public FallingObject
{
public:
    Trash(int x , int y , std::string spritepath, int spd, int num , bool ptouch , bool ftouch);
    ~Trash();
    void PlayerCatchTrash(int playerX, int playerY);
};

