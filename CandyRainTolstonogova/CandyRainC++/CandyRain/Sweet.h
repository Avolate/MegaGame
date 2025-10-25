#pragma once
#include "FallingObject.h"
#include "GameMain.h"
#include "Player.h"
class Sweet :
    public FallingObject
{
public:
    Sweet(int x, int y,  std::string spr, int spd, int num, bool ptouch, bool ftouch);
    ~Sweet();
    void PLayerCatchSweet(int playerX, int playerY);
    void SweetTouchFloor();
    void ChangeCandy(int &countcandy);
    void ChangeCake(int &countcake);
    void ChangeDonut(int &countdonut);
};

