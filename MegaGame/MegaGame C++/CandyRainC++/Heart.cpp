#include "Heart.h"

Heart::Heart(float x, float y, float velocity)
    : FallingObject(x, y, velocity), healthRestore(1) {
    // Здесь будет загрузка спрайта сердца
    // sprite.setTexture(...);
}

Heart::~Heart() {
}

void Heart::update(float deltaTime) {
    // Падение вниз
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
}

void Heart::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

int Heart::getHealthRestore() const {
    return healthRestore;
}
