#pragma once
#include "GameObject.h"
class FallingObject :
    public GameObject
{
private:
    int speed;
    int numb;
    bool player_touch;
    bool floor_touch;
public:
    FallingObject(int x , int y , std::string spritepath, int spd, int num , bool ptouch, bool ftouch);
    virtual ~FallingObject();
    void Falling();
    void MinusHealth(int &health);
    void DisplayInfo();
    // Getter
    int Getnumb() const;
    bool Getplayertouch() const;
    bool Getfloortouch() const;
    // Setter
    void Setnumb(int count);
    void Setplayertouch(bool count);
    void Setfloortouch(bool count);
};

