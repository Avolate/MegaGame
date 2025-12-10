#include "GameManager.h"
#include <sstream>
#include <iostream>

GameManager::GameManager()
	: window(sf::VideoMode(1500, 800), "Flying Danger"),
	currentState(GameState::PLAYING),
	score(0),
	archerHealth(3),
	castleHealth(3),
	archer(nullptr),
	castle(nullptr),
	bossBoulder(nullptr),
	spawnInterval(1.5f),
	bouldersOnScreen(0),
	bossActive(false),
	bgScrollX(0.0f)
{
	srand(static_cast<unsigned>(time(0)));
	window.setFramerateLimit(60);

	// Инициализация игровых объектов
	archer = new Archer();
	castle = new Castle();

	// Загружаем фоны (500x272)
	bgTexture1.loadFromFile("assets/Background_1.png");
	bgTexture2.loadFromFile("assets/Background_2.png");

	bgSprite1.setTexture(bgTexture1);
	bgSprite1.setScale(3.0f, 3.0f);
	bgSprite2.setTexture(bgTexture2);
	bgSprite2.setScale(3.0f, 3.0f);

	bgSprite2.setPosition(10, 0);
	bgSprite1.setPosition(10, 0);
	
	// ИСПРАВЛЕНО: Улучшена загрузка шрифта с поддержкой разных платформ
	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cerr << "Warning: Arial.ttf not found! Looking for alternative..." << std::endl;
		// Пробуем Windows путь
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		{
			// Пробуем Linux путь
			if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
			{
				std::cerr << "Error: No suitable font found!" << std::endl;
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

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}

		// Отслеживание позиции мыши
		if (event.type == sf::Event::MouseMoved)
		{
			archer->setMousePos(static_cast<float>(event.mouseMove.x),
				static_cast<float>(event.mouseMove.y));
		}

		// Выстрел при клике мыши
		if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left)
		{
			if (currentState == GameState::PLAYING)
			{
				// Создаём пулю из позиции архера
				sf::FloatRect archerBounds = archer->getBounds();
				Projectile* newProjectile = new Projectile(
					archerBounds.left + archerBounds.width,
					archerBounds.top + archerBounds.height / 2
				);
				projectiles.push_back(newProjectile);
			}
		}
	}
}

void GameManager::update(float deltaTime)
{
	if (currentState != GameState::PLAYING)
		return;

	// Обновление архера
	archer->update(deltaTime);

	// Спавнинг булыжников
	if (spawnTimer.getElapsedTime().asSeconds() > spawnInterval && bouldersOnScreen < 3)
	{
		spawnBoulder();
		spawnTimer.restart();
		spawnInterval = 1.2f + (rand() % 12) / 10.0f; // 1.2 - 2.4 сек
	}

	// Обновление булыжников
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

	// Обновление пуль
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

	// Обновление зелий
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

	// Обновление босса
	if (bossBoulder && bossBoulder->isActive)
	{
		bossBoulder->update(deltaTime);
	}

	// Проверка условия появления босса
	if (score >= 30 && !bossActive && bossBoulder == nullptr)
	{
		bossBoulder = new BossBoulder();
		bossActive = true;
	}

	// Проверка конца игры
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

	// Получаем bounds архера и замка
	sf::FloatRect archerBounds = archer->getBounds();
	sf::FloatRect castleBounds = castle->getBounds();

	// ===== ИСПРАВЛЕНО: КОЛЛИЗИЯ АРХЕРА С ЗАМКОМ =====
	// Это устраняет проблему, когда игрок проходил через замок
	if (archerBounds.intersects(castleBounds))
	{
		// Отталкиваем архера от замка (вправо)
		sf::FloatRect adjustedArcherBounds = archerBounds;
		adjustedArcherBounds.left = castleBounds.left + castleBounds.width + 10;
		archer->setPosition(adjustedArcherBounds.left, archerBounds.top);
	}

	// ===== ПУЛИ ↔ МЕТЕОРЫ (ОЧКО +1) =====
	for (int i = 0; i < projectiles.size(); i++)
	{
		sf::FloatRect projectileBounds = projectiles[i]->getBounds();

		for (int j = 0; j < boulders.size(); j++)
		{
			sf::FloatRect boulderBounds = boulders[j]->getBounds();

			if (projectileBounds.intersects(boulderBounds))
			{
				// Пуля попала в метеор - добавляем ОЧКО!
				score++;
				boulders[j]->isActive = false;
				projectiles[i]->isActive = false;
				break;
			}
		}
	}

	// ===== ПУЛИ ↔ БОС =====
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

	// ===== МЕТЕОРЫ ↔ АРХЕР (БЕЗ ОЧКА!) =====
	for (int i = 0; i < boulders.size(); i++)
	{
		sf::FloatRect boulderBounds = boulders[i]->getBounds();

		if (archerBounds.intersects(boulderBounds))
		{
			// Булыжник попал в архера - БЕЗ ОЧКА
			archerHealth--;
			boulders[i]->isActive = false;
		}
	}

	// ===== МЕТЕОРЫ ↔ ЗАМОК (БЕЗ ОЧКА!) =====
	for (int i = 0; i < boulders.size(); i++)
	{
		sf::FloatRect boulderBounds = boulders[i]->getBounds();

		if (castleBounds.intersects(boulderBounds))
		{
			// Булыжник попал в замок - БЕЗ ОЧКА
			castleHealth--;
			boulders[i]->isActive = false;
		}
	}

	// ===== БОС ↔ АРХЕР =====
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

	// ===== ЗЕЛЬЯ ↔ АРХЕР =====
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

	// Отрисовка фонов (тайлинг)
	window.draw(bgSprite2);
	window.draw(bgSprite1);

	// Отрисовка замка
	castle->draw(window);

	// Отрисовка булыжников
	for (auto b : boulders)
	{
		b->draw(window);
	}

	// Отрисовка пуль
	for (auto p : projectiles)
	{
		p->draw(window);
	}

	// Отрисовка зелий
	for (auto h : healthPotions)
	{
		h->draw(window);
	}

	// Отрисовка архера (последним, чтобы был сверху)
	archer->draw(window);

	// Отрисовка босса
	if (bossBoulder && bossBoulder->isActive)
	{
		bossBoulder->draw(window);
	}

	// Отрисовка HUD
	drawHUD();

	window.display();
}

void GameManager::drawHUD()
{
	// Фон HUD
	sf::RectangleShape hudBg(sf::Vector2f(1500, 100));
	hudBg.setFillColor(sf::Color(0, 0, 0, 180));
	window.draw(hudBg);

	// ИСПРАВЛЕНО: Правильная проверка шрифта с добавлением outline
	if (font.getInfo().family.length() > 0)
	{
		// ========== ПЕРВАЯ СТРОКА HUD ==========

		// Счётчик очков (ключевой параметр!) - ЖЁЛТЫЙ
		sf::Text scoreText("Score: " + std::to_string(score), font, 32);
		scoreText.setPosition(100, 5);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setOutlineThickness(2.0f);  // Контур для видимости
		scoreText.setOutlineColor(sf::Color::Black);
		window.draw(scoreText);

		// Здоровье архера - ЗЕЛЁНЫЙ
		sf::Text healthText("Player HP: " + std::to_string(archerHealth), font, 32);
		healthText.setPosition(1050, 15);
		healthText.setFillColor(sf::Color::Green);
		healthText.setOutlineThickness(2.0f);
		healthText.setOutlineColor(sf::Color::Black);
		window.draw(healthText);

		// ========== ВТОРАЯ СТРОКА HUD ==========

		// Здоровье замка - ГОЛУБОЙ
		sf::Text castleText("Castle HP: " + std::to_string(castleHealth), font, 32);
		castleText.setPosition(50, 48);
		castleText.setFillColor(sf::Color::Cyan);
		castleText.setOutlineThickness(2.0f);
		castleText.setOutlineColor(sf::Color::Black);
		window.draw(castleText);

		// Показываем информацию о босе если набрано 30 очков - КРАСНЫЙ
		if (score >= 30 && !bossActive)
		{
			sf::Text bossWarning("BOSS INCOMING!", font, 32);
			bossWarning.setPosition(450, 48);
			bossWarning.setFillColor(sf::Color::Red);
			bossWarning.setOutlineThickness(2.0f);
			bossWarning.setOutlineColor(sf::Color::Black);
			window.draw(bossWarning);
		}

		// Здоровье босса если он активен - ФИОЛЕТОВЫЙ
		if (bossBoulder && bossBoulder->isActive)
		{
			sf::Text bossHealth("Boss HP: " + std::to_string(bossBoulder->getHealth()), font, 32);
			bossHealth.setPosition(850, 48);
			bossHealth.setFillColor(sf::Color::Magenta);
			bossHealth.setOutlineThickness(2.0f);
			bossHealth.setOutlineColor(sf::Color::Black);
			window.draw(bossHealth);
		}
	}
	else
	{
		// Если шрифт не загружен, выводим диагностику
		std::cerr << "Font not available for HUD rendering!" << std::endl;
	}

	// Отрисовка сообщения о результате - GAME OVER
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

			sf::Text finalScoreText("Final Score: " + std::to_string(score), font, 48);
			finalScoreText.setPosition(400, 450);
			finalScoreText.setFillColor(sf::Color::White);
			finalScoreText.setOutlineThickness(2.0f);
			finalScoreText.setOutlineColor(sf::Color::Black);
			window.draw(finalScoreText);
		}
	}

	// Отрисовка сообщения о результате - WIN
	if (currentState == GameState::WIN)
	{
		sf::RectangleShape winBg(sf::Vector2f(1500, 800));
		winBg.setFillColor(sf::Color(0, 0, 0, 220));
		window.draw(winBg);

		if (font.getInfo().family.length() > 0)
		{
			sf::Text winText("YOU WIN!", font, 80);
			winText.setPosition(450, 300);
			winText.setFillColor(sf::Color::Green);
			winText.setOutlineThickness(3.0f);
			winText.setOutlineColor(sf::Color::Black);
			window.draw(winText);

			sf::Text finalScoreText("Final Score: " + std::to_string(score), font, 48);
			finalScoreText.setPosition(400, 450);
			finalScoreText.setFillColor(sf::Color::White);
			finalScoreText.setOutlineThickness(2.0f);
			finalScoreText.setOutlineColor(sf::Color::Black);
			window.draw(finalScoreText);
		}
	}
}
