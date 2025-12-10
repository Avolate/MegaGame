#pragma once

#include "FallingObject.h"

class Trash : public FallingObject {
private:
    int damage;

public:
    Trash(float x, float y, float velocity, sf::Texture& trashTex);
    virtual ~Trash();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    int getDamage() const;
};
