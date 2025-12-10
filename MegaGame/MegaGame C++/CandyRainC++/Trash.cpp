#include "Trash.h"

Trash::Trash(float x, float y, float velocity, sf::Texture& trashTex)
    : FallingObject(x, y, velocity), damage(1) {
    sprite.setTexture(trashTex);
    sprite.setScale(0.0185f, 0.0185f);  // 120×120
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

Trash::~Trash() {
}

void Trash::update(float deltaTime) {
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

void Trash::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

int Trash::getDamage() const {
    return damage;
}
