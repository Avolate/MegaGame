#pragma once
#include "GameObject.h"

class Button {
private:
    bool isPressed;
    int cooldownButton;

public:
    Button();
    ~Button();

    bool characterButtonContact(int characterPositionX, int characterPositionY);
    bool boxButtonContact(int boxPositionX, int boxPositionY);
    bool buttonChanges(bool wallBlockIsHide, bool spikeIsHide);

    // Getters
    bool getIsPressed() const;
    int getCooldownButton() const;

    // Setters
    void setIsPressed(bool pressed);
    void setCooldownButton(int cooldown);
}; 

