#include "Trash.h"

Trash::Trash(float x, float y, float velocity)
    : FallingObject(x, y, velocity), damage(1) {
    // Здесь будет загрузка спрайта мусора
    // sprite.setTexture(...);
}

Trash::~Trash() {
}

void Trash::update(float deltaTime) {
    // Падение вниз
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
}

void Trash::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

int Trash::getDamage() const {
    return damage;
}
