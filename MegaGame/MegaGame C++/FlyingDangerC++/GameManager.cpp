#include "GameManager.h"
#include <sstream>
#include <iostream>

GameManager::GameManager()
	: window(sf::VideoMode(1500, 800), "Flying Danger"),
	currentState(GameState::PLAYING),
	score(0),
	archerHealth(1),
	castleHealth(3),
	archer(nullptr),
	castle(nullptr),
	bossBoulder(nullptr),
	spawnInterval(0.8f),

	bouldersOnScreen(0),
	bossActive(false),
	bgScrollX(0.0f)
{
	srand(static_cast<unsigned>(time(0)));
	window.setFramerateLimit(60);

	archer = new Archer();
	castle = new Castle();

	bgTexture1.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\FlyingDangerC++\\assets\\Background_1.png");
	bgTexture2.loadFromFile("D:\\MegaGame\\MegaGame\\MegaGame C++\\FlyingDangerC++\\assets/Background_2.png");

	bgSprite2.setTexture(bgTexture2);
	bgSprite2.setScale(3.0f, 3.0f);
	bgSprite1.setTexture(bgTexture1);
	bgSprite1.setScale(3.0f, 3.0f);

	bgSprite2.setPosition(10, 0);
	bgSprite1.setPosition(10, 0);

	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cerr << "Warning Arial.ttf not found Looking for alternative" << std::endl;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		{
			if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
			{
				std::cerr << "Error No suitable font found" << std::endl;
			}
		}
	}
}

GameManager::~GameManager()
{
	delete archer;
	delete castle;
	if (bossBoulder) delete bossBoulder;
	for (auto b : boulders) delete b;
	for (auto p : projectiles) delete p;
	for (auto h : healthPotions) delete h;
}

void GameManager::run()
{
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		handleInput();
		update(deltaTime);
		checkCollisions();
		render();
	}
}

void GameManager::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (currentState == GameState::PLAYING)
				{
					currentState = GameState::PAUSED;
				}
				else if (currentState == GameState::PAUSED)
				{
					currentState = GameState::PLAYING;
				}
			}

			if (currentState == GameState::PAUSED)
			{
				if (event.key.code == sf::Keyboard::C)
				{
					currentState = GameState::PLAYING;
				}

				if (event.key.code == sf::Keyboard::R)
				{
					restartGame();
					currentState = GameState::PLAYING;
				}

				if (event.key.code == sf::Keyboard::M)
				{
					window.close();
				}
			}
			if (currentState == GameState::GAME_OVER || currentState == GameState::WIN)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					restartGame();
					currentState = GameState::PLAYING;
				}

				if (event.key.code == sf::Keyboard::M)
				{
					window.close();
				}
			}
		}

		if (event.type == sf::Event::MouseMoved && currentState == GameState::PLAYING)
		{
			archer->setMousePos(static_cast<float>(event.mouseMove.x),
				static_cast<float>(event.mouseMove.y));
		}

		if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left &&
			currentState == GameState::PLAYING)
		{
			sf::FloatRect archerBounds = archer->getBounds();
			Projectile* newProjectile = new Projectile(
				archerBounds.left + archerBounds.width,
				archerBounds.top + archerBounds.height / 2
			);
			projectiles.push_back(newProjectile);
		}
	}
}

void GameManager::update(float deltaTime)
{
	if (currentState != GameState::PLAYING)
		return;

	archer->update(deltaTime);

	if (spawnTimer.getElapsedTime().asSeconds() > spawnInterval && bouldersOnScreen < 4)  // Увеличили лимит до 4
	{
		// Шанс множественного спавна (30%)
		int spawnCount = 1;
		if (multiSpawnChance > (rand() % 100) / 100.0f && bouldersOnScreen < 3)
		{
			spawnCount = 2 + (rand() % 2);  // 2 или 3 метеора
		}

		// Спавним нужное количество метеоров
		for (int i = 0; i < spawnCount; i++)
		{
			spawnBoulder();
		}

		spawnTimer.restart();
		spawnInterval = 0.8f + (rand() % 8) / 10.0f;  // Частота 0.8-1.6 сек
		bouldersOnScreen = std::min(bouldersOnScreen, 4);  // Ограничиваем максимум
	}

	for (int i = 0; i < boulders.size(); i++)
	{
		boulders[i]->update(deltaTime);
		if (!boulders[i]->isActive)
		{
			delete boulders[i];
			boulders.erase(boulders.begin() + i);
			bouldersOnScreen--;
			i--;
		}
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->update(deltaTime);
		if (!projectiles[i]->isActive)
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < healthPotions.size(); i++)
	{
		healthPotions[i]->update(deltaTime);
		if (!healthPotions[i]->isActive)
		{
			delete healthPotions[i];
			healthPotions.erase(healthPotions.begin() + i);
			i--;
		}
	}

	if (bossBoulder && bossBoulder->isActive)
	{
		bossBoulder->update(deltaTime);
	}

	if (score >= 30 && !bossActive && bossBoulder == nullptr)
	{
		bossBoulder = new BossBoulder();
		bossActive = true;
	}

	if (castleHealth <= 0 || archerHealth <= 0)
	{
		currentState = GameState::GAME_OVER;
	}

	if (bossActive && bossBoulder && bossBoulder->getHealth() <= 0)
	{
		currentState = GameState::WIN;
	}
}

void GameManager::checkCollisions()
{
	if (currentState != GameState::PLAYING)
		return;

	sf::FloatRect archerBounds = archer->getBounds();
	sf::FloatRect platformBounds = archer->getPlatformBounds();
	sf::FloatRect castleBounds = castle->getBounds();

	if (archerBounds.intersects(castleBounds))
	{
		sf::FloatRect adjustedArcherBounds = archerBounds;
		adjustedArcherBounds.left = castleBounds.left + castleBounds.width + 10;
		archer->setPosition(adjustedArcherBounds.left, archerBounds.top);
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		sf::FloatRect projectileBounds = projectiles[i]->getBounds();

		for (int j = 0; j < boulders.size(); j++)
		{
			sf::FloatRect boulderBounds = boulders[j]->getBounds();

			if (projectileBounds.intersects(boulderBounds))
			{
				score++;
				boulders[j]->isActive = false;
				projectiles[i]->isActive = false;
				break;
			}
		}
	}

	if (bossBoulder && bossBoulder->isActive)
	{
		sf::FloatRect bossBounds = bossBoulder->getBounds();

		for (int i = 0; i < projectiles.size(); i++)
		{
			sf::FloatRect projectileBounds = projectiles[i]->getBounds();

			if (projectileBounds.intersects(bossBounds))
			{
				bossBoulder->takeDamage(1);
				projectiles[i]->isActive = false;
			}
		}
	}

	for (int i = 0; i < boulders.size(); i++)
	{
		sf::FloatRect boulderBounds = boulders[i]->getBounds();

		if (platformBounds.intersects(boulderBounds))
		{
			boulders[i]->isActive = false;
		}
	}

	for (int i = 0; i < boulders.size(); i++)
	{
		sf::FloatRect boulderBounds = boulders[i]->getBounds();

		if (archerBounds.intersects(boulderBounds))
		{
			archerHealth--;
			boulders[i]->isActive = false;
		}
	}

	for (int i = 0; i < boulders.size(); i++)
	{
		sf::FloatRect boulderBounds = boulders[i]->getBounds();

		if (castleBounds.intersects(boulderBounds))
		{
			castleHealth--;
			boulders[i]->isActive = false;
		}
	}

	if (bossBoulder && bossBoulder->isActive)
	{
		sf::FloatRect bossBounds = bossBoulder->getBounds();

		if (archerBounds.intersects(bossBounds))
		{
			archerHealth = 0;
		}

		if (castleBounds.intersects(bossBounds))
		{
			castleHealth = 0;
		}
	}

	for (int i = 0; i < healthPotions.size(); i++)
	{
		sf::FloatRect potionBounds = healthPotions[i]->getBounds();

		if (archerBounds.intersects(potionBounds))
		{
			if (archerHealth < 3)
				archerHealth++;
			healthPotions[i]->isActive = false;
		}
	}
}

void GameManager::spawnBoulder()
{
	Boulder* newBoulder = new Boulder();
	boulders.push_back(newBoulder);
	bouldersOnScreen++;
}

void GameManager::render()
{
	window.clear(sf::Color::Black);
	
	window.draw(bgSprite2);
	window.draw(bgSprite1);

	castle->draw(window);

	for (auto b : boulders)
	{
		b->draw(window);
	}

	for (auto p : projectiles)
	{
		p->draw(window);
	}

	for (auto h : healthPotions)
	{
		h->draw(window);
	}

	archer->draw(window);

	if (bossBoulder && bossBoulder->isActive)
	{
		bossBoulder->draw(window);
	}

	drawHUD();

	if (currentState == GameState::PAUSED)
	{
		drawPauseMenu();
	}

	if (currentState == GameState::GAME_OVER || currentState == GameState::WIN)
	{
		drawGameOverMenu();
	}

	window.display();
}

void GameManager::drawHUD()
{
	sf::RectangleShape hudBg(sf::Vector2f(1500, 80));
	hudBg.setFillColor(sf::Color(0, 0, 0, 180));
	window.draw(hudBg);

	if (font.getInfo().family.length() > 0)
	{
		sf::Text scoreText("Score. " + std::to_string(score), font, 32);
		scoreText.setPosition(50, 5);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setOutlineThickness(2.0f);
		scoreText.setOutlineColor(sf::Color::Black);
		window.draw(scoreText);

		sf::Text healthText("Player HP. " + std::to_string(archerHealth), font, 32);
		healthText.setPosition(1000, 20);
		healthText.setFillColor(sf::Color::Green);
		healthText.setOutlineThickness(2.0f);
		healthText.setOutlineColor(sf::Color::Black);
		window.draw(healthText);

		sf::Text castleText("Castle HP. " + std::to_string(castleHealth), font, 32);
		castleText.setPosition(50, 40);
		castleText.setFillColor(sf::Color::Cyan);
		castleText.setOutlineThickness(2.0f);
		castleText.setOutlineColor(sf::Color::Black);
		window.draw(castleText);

		if (score >= 25 && !bossActive)
		{
			sf::Text bossWarning("BOSS INCOMING.", font, 32);
			bossWarning.setPosition(500, 20);
			bossWarning.setFillColor(sf::Color::Red);
			bossWarning.setOutlineThickness(2.0f);
			bossWarning.setOutlineColor(sf::Color::Black);
			window.draw(bossWarning);
		}

		if (bossBoulder && bossBoulder->isActive)
		{
			sf::Text bossHealth("Boss HP. " + std::to_string(bossBoulder->getHealth()), font, 32);
			bossHealth.setPosition(500, 20);
			bossHealth.setFillColor(sf::Color::Magenta);
			bossHealth.setOutlineThickness(2.0f);
			bossHealth.setOutlineColor(sf::Color::Black);
			window.draw(bossHealth);
		}
	}

	if (currentState == GameState::GAME_OVER)
	{
		sf::RectangleShape gameOverBg(sf::Vector2f(1500, 800));
		gameOverBg.setFillColor(sf::Color(0, 0, 0, 220));
		window.draw(gameOverBg);

		if (font.getInfo().family.length() > 0)
		{
			sf::Text gameOverText("GAME OVER", font, 80);
			gameOverText.setPosition(400, 300);
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setOutlineThickness(3.0f);
			gameOverText.setOutlineColor(sf::Color::Black);
			window.draw(gameOverText);

			sf::Text finalScoreText("Final Score. " + std::to_string(score), font, 48);
			finalScoreText.setPosition(400, 400);
			finalScoreText.setFillColor(sf::Color::White);
			finalScoreText.setOutlineThickness(2.0f);
			finalScoreText.setOutlineColor(sf::Color::Black);
			window.draw(finalScoreText);
		}
	}

	if (currentState == GameState::WIN)
	{
		sf::RectangleShape winBg(sf::Vector2f(1500, 800));
		winBg.setFillColor(sf::Color(0, 0, 0, 220));
		window.draw(winBg);

		if (font.getInfo().family.length() > 0)
		{
			sf::Text winText("YOU WIN.", font, 80);
			winText.setPosition(450, 300);
			winText.setFillColor(sf::Color::Green);
			winText.setOutlineThickness(3.0f);
			winText.setOutlineColor(sf::Color::Black);
			window.draw(winText);

			sf::Text finalScoreText("Final Score. " + std::to_string(score), font, 48);
			finalScoreText.setPosition(450, 450);
			finalScoreText.setFillColor(sf::Color::White);
			finalScoreText.setOutlineThickness(2.0f);
			finalScoreText.setOutlineColor(sf::Color::Black);
			window.draw(finalScoreText);
		}
	}
}

void GameManager::drawPauseMenu()
{
	sf::RectangleShape pauseBg(sf::Vector2f(1500, 800));
	pauseBg.setFillColor(sf::Color(0, 0, 0, 200));
	window.draw(pauseBg);

	if (font.getInfo().family.length() > 0)
	{
		sf::Text pauseTitle("PAUSE", font, 80);
		pauseTitle.setPosition(550, 150);
		pauseTitle.setFillColor(sf::Color::Yellow);
		pauseTitle.setOutlineThickness(3.0f);
		pauseTitle.setOutlineColor(sf::Color::Black);
		window.draw(pauseTitle);

		sf::Text continueText("C. Continue", font, 48);
		continueText.setPosition(550, 300);
		continueText.setFillColor(sf::Color::Green);
		continueText.setOutlineThickness(2.0f);
		continueText.setOutlineColor(sf::Color::Black);
		window.draw(continueText);

		sf::Text restartText("R. Restart", font, 48);
		restartText.setPosition(550, 400);
		restartText.setFillColor(sf::Color::Yellow);
		restartText.setOutlineThickness(2.0f);
		restartText.setOutlineColor(sf::Color::Black);
		window.draw(restartText);

		sf::Text menuText("M. Exit to Menu", font, 48);
		menuText.setPosition(550, 500);
		menuText.setFillColor(sf::Color::Red);
		menuText.setOutlineThickness(2.0f);
		menuText.setOutlineColor(sf::Color::Black);
		window.draw(menuText);
	}
}

void GameManager::drawGameOverMenu()
{
	sf::RectangleShape endGameBg(sf::Vector2f(1500, 800));
	endGameBg.setFillColor(sf::Color(0, 0, 0, 220));
	window.draw(endGameBg);

	if (font.getInfo().family.length() > 0)
	{
		sf::Text titleText("", font, 80);
		sf::Color titleColor;

		if (currentState == GameState::GAME_OVER)
		{
			titleText.setString("GAME OVER");
			titleColor = sf::Color::Red;
		}
		else if (currentState == GameState::WIN)
		{
			titleText.setString("YOU WIN.");
			titleColor = sf::Color::Green;
		}

		titleText.setPosition(400, 150);
		titleText.setFillColor(titleColor);
		titleText.setOutlineThickness(3.0f);
		titleText.setOutlineColor(sf::Color::Black);
		window.draw(titleText);

		sf::Text finalScoreText("Final Score. " + std::to_string(score), font, 48);
		finalScoreText.setPosition(400, 280);
		finalScoreText.setFillColor(sf::Color::White);
		finalScoreText.setOutlineThickness(2.0f);
		finalScoreText.setOutlineColor(sf::Color::Black);
		window.draw(finalScoreText);

		sf::Text restartText("R. Play Again", font, 48);
		restartText.setPosition(450, 420);
		restartText.setFillColor(sf::Color::Green);
		restartText.setOutlineThickness(2.0f);
		restartText.setOutlineColor(sf::Color::Black);
		window.draw(restartText);

		sf::Text exitText("M. Exit to Menu", font, 48);
		exitText.setPosition(450, 480);
		exitText.setFillColor(sf::Color::Red);
		exitText.setOutlineThickness(2.0f);
		exitText.setOutlineColor(sf::Color::Black);
		window.draw(exitText);
	}
}

void GameManager::restartGame()
{
	for (auto b : boulders) delete b;
	for (auto p : projectiles) delete p;
	for (auto h : healthPotions) delete h;
	if (bossBoulder) delete bossBoulder;

	boulders.clear();
	projectiles.clear();
	healthPotions.clear();
	bossBoulder = nullptr;

	score = 0;
	archerHealth = 1;
	castleHealth = 3;
	bouldersOnScreen = 0;
	bossActive = false;

	delete archer;
	delete castle;
	archer = new Archer();
	castle = new Castle();

	spawnTimer.restart();
	spawnInterval = 1.5f;
}
