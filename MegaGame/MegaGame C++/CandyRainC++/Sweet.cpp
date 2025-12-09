#include "Sweet.h"
#include <cstdlib>
#include <ctime>>

Sweet::Sweet(float x, float y, float velocity)
    : FallingObject(x, y, velocity) {
    // Случайный выбор типа сладости
    srand(static_cast<unsigned>(time(0)));
    int typeIndex = rand() % 3;
    type = static_cast<SweetType>(typeIndex);

    // Установка очков в зависимости от типа
    switch (type) {
    case SweetType::CANDY:
        points = 10;
        break;
    case SweetType::DONUT:
        points = 20;
        break;
    case SweetType::CAKE:
        points = 30;
        break;
    }

    // Здесь будет загрузка спрайта в зависимости от типа
    // sprite.setTexture(...);
}

Sweet::~Sweet() {
}

void Sweet::update(float deltaTime) {
    // Падение вниз
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
}

void Sweet::draw(sf::RenderWindow& window) {
    if (isActive) {
        window.draw(sprite);
    }
}

SweetType Sweet::getType() const {
    return type;
}

int Sweet::getPoints() const {
    return points;
}
