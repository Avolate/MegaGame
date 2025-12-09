#ifndef SWEET_H
#define SWEET_H

#include "FallingObject.h"

enum class SweetType {
    CANDY,
    DONUT,
    CAKE
};

class Sweet : public FallingObject {
private:
    SweetType type;
    int points;

public:
    Sweet(float x, float y, float velocity);
    virtual ~Sweet();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    SweetType getType() const;
    int getPoints() const;
};

#endif
