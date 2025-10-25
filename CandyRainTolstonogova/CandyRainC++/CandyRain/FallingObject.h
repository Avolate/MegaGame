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
    FallingObject(int x , int y , std::string sprite_path, int spd, int num , bool p_touch, bool f_touch);
    virtual ~FallingObject();
    void falling();
    void minusHealth(int &health);
    void displayInfo();
    // Getter
    int getnumb() const;
    bool getplayer_touch() const;
    bool getfloor_touch() const;
    // Setter
    void setnumb(int count);
    void setplayer_touch(bool count);
    void setfloor_touch(bool count);
};

