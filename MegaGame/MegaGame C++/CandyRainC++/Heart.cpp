#include "Heart.h"

Heart::Heart(float x, float y, float velocity, sf::Texture& heartTex)
    : FallingObject(x, y, velocity), healthRestore(1) {
    sprite.setTexture(heartTex);
    sprite.setScale(0.0140f, 0.0135f);  // 80×70
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

Heart::~Heart() {
}

void Heart::update(float deltaTime) {
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

void Heart::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

int Heart::getHealthRestore() const {
    return healthRestore;
}
