#pragma once
#include "FallingObject.h"
#include "Player.h"
class Trash :
    public FallingObject
{
public:
    Trash(int x , int y , std::string sprite_path, int spd, int num , bool p_touch , bool f_touch);
    ~Trash();
    void playerCatchTrash(int playerX, int playerY);
};

