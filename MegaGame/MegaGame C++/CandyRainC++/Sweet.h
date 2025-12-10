#pragma once

#include "FallingObject.h"

enum class SweetType {
    CANDY,
    DONUT,
    LOLLIPOP,
    CAKE
};

class Sweet : public FallingObject {
private:
    SweetType type;
    int points;

    void randomizeType();

public:
    Sweet(float x, float y, float velocity, sf::Texture& candyTex,
        sf::Texture& donutTex, sf::Texture& lollipopTex, sf::Texture& cakeTex);
    virtual ~Sweet();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    SweetType getType() const;
    int getPoints() const;
};
