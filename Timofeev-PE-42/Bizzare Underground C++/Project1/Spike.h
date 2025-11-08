#pragma once
#include "GameObject.h"

class Spike {
private:
    bool isHide;

public:
    Spike();
    ~Spike();

    bool characterSpikeContact(int characterPositionX, int characterPositionY);
    void putingSpike();

    // Getter
    bool getIsHide() const;

    // Setter
    void setIsHide(bool hide);
};

 