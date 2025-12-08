#pragma once
#include "GameObject.h"

class Castle : public GameObject
{
public:
    Castle();
    virtual ~Castle() = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    int getHealth() const { return health; }
    void takeDamage(int damage) { health -= damage; }

private:
    sf::RectangleShape shape;
    int health;
};
