#pragma once
#include "GameObject.h"

class Box {
private:
    bool isHanged;
    int speedFalling;
    int speedMovement;

public:
    Box();
    ~Box();

    void checkHanged();
    void fallingBox();
    void movementBox();
    bool characterBoxContact(int characterPositionX, int characterPositionY);

    // Getters
    bool getIsHanged() const;
    int getSpeedFalling() const;
    int getSpeedMovement() const;

    // Setters
    void setIsHanged(bool hanged);
    void setSpeedFalling(int sf);
    void setSpeedMovement(int sm);
};
