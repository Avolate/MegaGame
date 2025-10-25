#pragma once
#include "GameObject.h"

class Character : public GameObject {
private:
    bool isAlive;
    int speedCharacter;
    bool isHanged;

public:
    Character();
    ~Character();

    void movementRight();
    void movementLeft();
    void jump();
    void fallingCharacter();

    // Getters
    bool getIsAlive() const;
    int getSpeedCharacter() const;
    bool getIsHanged() const;

    // Setters
    void setIsAlive(bool alive);
    void setSpeedCharacter(int speed);
    void setIsHanged(bool hanged);
};
