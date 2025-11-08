#pragma once
#include "GameObject.h"

class Dart {
private:
    int speed;
    int spawnSpeed;
    bool status;

public:
    Dart();
    ~Dart();

    bool characterDartContact(int characterPositionX, int characterPositionY);
    bool dartWallContact(int wallBlockPositionX, int wallBlockPositionY);
    bool dartBoxContact(int boxPositionX, int boxPositionY);
    void dartFlight();
    void dartDestroy();

    // Getters
    int getSpeed() const;
    int getSpawnSpeed() const;
    bool getStatus() const;

    // Setters
    void setSpeed(int s);
    void setSpawnSpeed(int ss);
    void setStatus(bool st);
};
 

