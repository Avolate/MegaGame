#pragma once

#include "GameObject.h"

class Door {
private:
    int keyCounter;

public:
    Door();
    ~Door();

    static const int max_keys = 3;

    void doorOpen();

    // Getter
    int getKeyCounter() const;

    // Setter
    void setKeyCounter(int count);
};
 