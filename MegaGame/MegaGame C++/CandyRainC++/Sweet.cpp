#include "Sweet.h"
#include <cstdlib>
#include <ctime>

Sweet::Sweet(float x, float y, float velocity, sf::Texture& candyTex,
    sf::Texture& donutTex, sf::Texture& lollipopTex, sf::Texture& cakeTex)
    : FallingObject(x, y, velocity) {
    randomizeType();

    switch (type) {
    case SweetType::CANDY:
        sprite.setTexture(candyTex);
        sprite.setScale(0.0267f, 0.0267f);  // 80×80
        points = 10;
        break;
    case SweetType::DONUT:
        sprite.setTexture(donutTex);
        sprite.setScale(0.0235f, 0.0235f);  // 100×100
        points = 20;
        break;
    case SweetType::LOLLIPOP:
        sprite.setTexture(lollipopTex);
        sprite.setScale(0.0267f, 0.0267f);  // 80×80
        points = 30;
        break;
    case SweetType::CAKE:
        sprite.setTexture(cakeTex);
        sprite.setScale(0.0267f, 0.0267f);  // 80×80
        points = 25;
        break;
    }

    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

Sweet::~Sweet() {
}

void Sweet::randomizeType() {
    int typeIndex = rand() % 4;
    type = static_cast<SweetType>(typeIndex);
}

void Sweet::update(float deltaTime) {
    position.y += velocity * deltaTime;
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
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
