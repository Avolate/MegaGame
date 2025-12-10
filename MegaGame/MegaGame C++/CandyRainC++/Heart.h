#pragma once

#include "FallingObject.h"

class Heart : public FallingObject {
private:
    int healthRestore;

public:
    Heart(float x, float y, float velocity, sf::Texture& heartTex);
    virtual ~Heart();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    int getHealthRestore() const;
};
