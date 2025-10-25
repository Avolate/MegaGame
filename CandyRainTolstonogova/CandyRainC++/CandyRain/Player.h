#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
private:
    int speed;
    bool life;
public:
    Player(int x , int y , const std::string& spritepath , int spd , bool alive );
    ~Player();
    void MoveRight();
    void MoveLeft();
    // Getter
    int GetLife() const;

    // Setter
    void SetLife(int count);
};

