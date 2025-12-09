#ifndef TRASH_H
#define TRASH_H

#include "FallingObject.h"

class Trash : public FallingObject {
private:
    int damage;

public:
    Trash(float x, float y, float velocity);
    virtual ~Trash();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    int getDamage() const;
};

#endif
