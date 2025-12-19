#pragma once
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Spike.h"
#include "Key.h"
#include "Door.h"
#include "Box.h"
#include "Button.h"
#include "Dart.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;

    // ========== ФОН ==========
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    // =======================

    Player player;
    Box* spawnedBox;
    Button button;
    Button button2;  // Вторая кнопка для платформ
    Button button3;  // Третья кнопка для временной платформы с задержкой

    std::vector<Ground> grounds;
    std::vector<Ground> temporaryGrounds;  // Временные платформы
    std::vector<Ground> delayedGrounds;    // Платформы с задержкой исчезновения
    std::vector<Spike> spikes;
    std::vector<Key> keys;
    std::vector<Dart> darts;

    Door door;

    sf::Clock gameClock;
    sf::Clock dartSpawner;
    sf::Clock delayedPlatformTimer;  // Таймер для платформы с задержкой

    int keysCollected;
    bool buttonActivated;
    bool platformsActive;  // Видны ли платформы?
    bool button3Pressed;   // Была ли нажата кнопка 3?
    bool delayedPlatformActive; // Активна ли платформа с задержкой?
    bool gameOver;  // Проиграл ли игрок?
    bool isPaused;  // На паузе ли игра?
    bool levelComplete;  // Уровень пройден?

    const float WINDOW_WIDTH = 1200.0f;
    const float WINDOW_HEIGHT = 800.0f;
    const float DART_SPAWN_INTERVAL = 2.0f;
    const float DELAYED_PLATFORM_DURATION = 2.0f;  // 2 секунды

    // Начальная позиция персонажа
    const float PLAYER_START_X = 100.0f;
    const float PLAYER_START_Y = 550.0f;

public:
    Game();
    ~Game();

    void initializeLevel();
    void handleEvents();
    void handleMouseClick(int x, int y);
    void update();
    void render();
    void renderGameOver();
    void renderPauseMenu();
    void renderLevelComplete();
    void checkCollisions();
    void spawnDart();
    void resetLevel();
    void resetKeysAndDoor();

    void run();
    bool isRunning() const;
};