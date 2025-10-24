#include "Dart.h"
#include <iostream>

Dart::Dart() : speed(3), spawnSpeed(50), status(true) {
    std::cout << "--- Dart Initialized ---" << std::endl;
    std::cout << "  Speed: " << getSpeed() << std::endl;
    std::cout << "  Spawn Speed: " << getSpawnSpeed() << std::endl;
    std::cout << "  Status: " << std::boolalpha << getStatus() << std::endl;
}

Dart::~Dart() {
    std::cout << "--- Dart Destroyed ---" << std::endl;
    std::cout << "  Final Status: " << std::boolalpha << getStatus() << std::endl;
}

bool Dart::characterDartContact(int characterPositionX, int characterPositionY) {
    std::cout << "Dart::characterDartContact() called. Checking Character(" << characterPositionX << ", " << characterPositionY << ") against Dart." << std::endl;
    return false;
}

bool Dart::dartWallContact(int wallBlockPositionX, int wallBlockPositionY) {
    std::cout << "Dart::dartWallContact() called. Checking WallBlock(" << wallBlockPositionX << ", " << wallBlockPositionY << ") against Dart." << std::endl;
    return false;
}

bool Dart::dartBoxContact(int boxPositionX, int boxPositionY) {
    std::cout << "Dart::dartBoxContact() called. Checking Box(" << boxPositionX << ", " << boxPositionY << ") against Dart." << std::endl;
    return false;
}

void Dart::dartFlight() {
    std::cout << "Dart::dartFlight() called. Simulating flight." << std::endl;
}

void Dart::dartDestroy() {
    std::cout << "Dart::dartDestroy() called. Current status: " << std::boolalpha << getStatus() << std::endl;
    setStatus(false);
    std::cout << "Dart::dartDestroy(): Dart destroyed. New status: " << std::boolalpha << getStatus() << std::endl;
}

int Dart::getSpeed() const { return speed; }
int Dart::getSpawnSpeed() const { return spawnSpeed; }
bool Dart::getStatus() const { return status; }

void Dart::setSpeed(int s) {
    speed = s;
    std::cout << "Dart::setSpeed() called. New speed: " << speed << std::endl;
}
void Dart::setSpawnSpeed(int ss) {
    spawnSpeed = ss;
    std::cout << "Dart::setSpawnSpeed() called. New spawnSpeed: " << spawnSpeed << std::endl;
}
void Dart::setStatus(bool st) {
    status = st;
    std::cout << "Dart::setStatus() called. New status: " << std::boolalpha << status << std::endl;
}