#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
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
	void spawnBoulder();
	void spawnBackground();
	void drawHUD();
	void checkCollisions();

	sf::RenderWindow window;
	GameState currentState;

	Archer* archer;
	Castle* castle;
	std::vector<Boulder*> boulders;
	std::vector<Projectile*> projectiles;
	std::vector<HealthPotion*> healthPotions;
	BossBoulder* bossBoulder;

	// Фоны
	sf::Texture bgTexture1, bgTexture2;
	sf::Sprite bgSprite1, bgSprite2;
	float bgScrollX;

	// Счётчики
	int score;
	int archerHealth;
	int castleHealth;

	// Время и спавнинг
	sf::Clock clock;
	sf::Clock spawnTimer;
	float spawnInterval;
	int bouldersOnScreen;

	// Шрифт для HUD
	sf::Font font;

	// Флаг для отслеживания активности босса
	bool bossActive;
};
