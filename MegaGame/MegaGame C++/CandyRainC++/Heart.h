#ifndef HEART_H
#define HEART_H

#include "FallingObject.h"

class Heart : public FallingObject {
private:
    int healthRestore;

public:
    Heart(float x, float y, float velocity);
    virtual ~Heart();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    int getHealthRestore() const;
};

#endif
