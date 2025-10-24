#pragma once
#include "GameObject.h"

class Key {
public:
    Key();
    ~Key();

    bool characterKeyContact(int characterPositionX, int characterPositionY);
    int keyDestroy(int keyCounter);
};
 