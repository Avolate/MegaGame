#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Archer.h"
#include "Boulder.h"
#include "BossBoulder.h"
#include "Projectile.h"
#include "Castle.h"
#include "HealthPotion.h"

enum class GameState
{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
};

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void run();

private:
    void handleInput();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    GameState currentState;

    // Игровые объекты
    Archer* archer;
    Castle* castle;

    std::vector<Boulder*> boulders;
    std::vector<Projectile*> projectiles;
    std::vector<HealthPotion*> healthPotions;

    BossBoulder* bossBoulder;

    // Счётчики
    int destroyedBoulders;
    int archerHealth;
    int castleHealth;

    // Время
    sf::Clock clock;
};
