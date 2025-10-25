#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
private:
    int speed;
    bool life;
public:
    Player(int x , int y , const std::string& sprite_path , int spd , bool alive );
    ~Player();
    void moveRight();
    void moveLeft();
    // Getter
    int getlife() const;

    // Setter
    void setlife(int count);
};

