#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>

class GameLauncher {
public:
    static HANDLE LaunchGame(const std::string& gamePath);
    static void WaitForGameExit(HANDLE gameProcess);
};

// GameLauncher.cpp
#include <iostream>

HANDLE GameLauncher::LaunchGame(const std::string& gamePath) {
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

    // Преобразуем путь в абсолютный
    char fullPath[MAX_PATH];
    GetFullPathNameA(gamePath.c_str(), MAX_PATH, fullPath, nullptr);

    std::cout << "Запуск игры: " << fullPath << std::endl;

    // Создаём процесс
    if (CreateProcessA(
        fullPath,           // Полный путь к .exe файлу
        nullptr,            // Аргументы командной строки (не требуются)
        nullptr,            // Дескриптор защиты процесса (по умолчанию)
        nullptr,            // Дескриптор защиты потока (по умолчанию)
        FALSE,              // Наследование дескрипторов
        0,                  // Флаги создания (нормальное создание)
        nullptr,            // Переменные окружения (наследуем)
        nullptr,            // Рабочая директория (текущая)
        &si,
        &pi
    )) {
        std::cout << "Игра запущена успешно! PID: " << pi.dwProcessId << std::endl;
        CloseHandle(pi.hThread); // Закрываем дескриптор потока (не нужен)
        return pi.hProcess;      // Возвращаем дескриптор процесса для отслеживания
    }
    else {
        std::cerr << "Ошибка запуска игры. Код ошибки: " << GetLastError() << std::endl;
        return nullptr;
    }
}

void GameLauncher::WaitForGameExit(HANDLE gameProcess) {
    if (gameProcess) {
        std::cout << "Ожидаем завершения игры..." << std::endl;
        WaitForSingleObject(gameProcess, INFINITE); // Бесконечно ждём выхода
        CloseHandle(gameProcess); // Закрываем дескриптор
        std::cout << "✓ Игра завершена, возвращаемся в меню" << std::endl;
    }
}

// main.cpp - Главный класс лаунчера с меню
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class MainMenu {
private:
    enum MenuItem {
        FLYING_DANGER = 0,
        CANDY_RAIN = 1,
        BIZZARE_UNDERGROUND = 2,
        ABOUT = 3,
        EXIT = 4,
        NONE = -1
    };

    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int selectedIndex = 0;
    const int ITEM_COUNT = 5;

    // Цветовые переменные
    sf::Color colorSelected = sf::Color(100, 200, 255);    // Голубой
    sf::Color colorUnselected = sf::Color(200, 200, 200);  // Серый
    sf::Color colorHover = sf::Color(150, 220, 255);       // Более яркий голубой

    float hoverBobbing = 0.f;
    float bobSpeed = 0.05f;

public:
    MainMenu() : window(sf::VideoMode(1024, 768), "Game Launcher", sf::Style::Close) {
        window.setFramerateLimit(60);

        // Загружаем шрифт (убедись, что файл существует!)
        if (!font.loadFromFile("resources/fonts/arial.ttf")) {
            if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                std::cerr << "Ошибка: не удалось загрузить шрифт!" << std::endl;
            }
        }

        // Инициализируем элементы меню
        InitializeMenu();
    }

    void InitializeMenu() {
        // Заголовок
        title.setFont(font);
        title.setString("GAME LAUNCHER");
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::White);

        // Центрируем заголовок по X
        float titleX = (window.getSize().x - title.getLocalBounds().width) / 2.f;
        title.setPosition(titleX, 50.f);

        // Названия игр и пунктов меню
        std::vector<std::string> itemNames = {
            "1. Flying Danger",
            "2. Candy Rain",
            "3. Bizzare Underground",
            "4. Об авторах",
            "5. Выход"
        };

        float startY = 200.f;
        float itemSpacing = 80.f;

        for (size_t i = 0; i < itemNames.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(itemNames[i]);
            item.setCharacterSize(40);
            item.setFillColor(colorUnselected);

            // Центрируем по X
            float itemX = (window.getSize().x - item.getLocalBounds().width) / 2.f;
            item.setPosition(itemX, startY + i * itemSpacing);

            menuItems.push_back(item);
        }

        // По умолчанию выбран первый элемент
        selectedIndex = 0;
        UpdateMenuSelection();
    }

    void UpdateMenuSelection() {
        // Очищаем все цвета
        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (i == selectedIndex) {
                menuItems[i].setFillColor(colorSelected);
                menuItems[i].setCharacterSize(45);
            }
            else {
                menuItems[i].setFillColor(colorUnselected);
                menuItems[i].setCharacterSize(40);
            }
        }
    }

    void HandleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    selectedIndex = (selectedIndex - 1 + ITEM_COUNT) % ITEM_COUNT;
                    UpdateMenuSelection();
                    break;

                case sf::Keyboard::Down:
                    selectedIndex = (selectedIndex + 1) % ITEM_COUNT;
                    UpdateMenuSelection();
                    break;

                case sf::Keyboard::Return:
                case sf::Keyboard::Space:
                    ExecuteMenuAction(selectedIndex);
                    break;

                case sf::Keyboard::Escape:
                    window.close();
                    break;

                    // Быстрый доступ по цифрам 1-5
                case sf::Keyboard::Num1:
                    ExecuteMenuAction(FLYING_DANGER);
                    break;
                case sf::Keyboard::Num2:
                    ExecuteMenuAction(CANDY_RAIN);
                    break;
                case sf::Keyboard::Num3:
                    ExecuteMenuAction(BIZZARE_UNDERGROUND);
                    break;
                case sf::Keyboard::Num4:
                    ExecuteMenuAction(ABOUT);
                    break;
                case sf::Keyboard::Num5:
                    ExecuteMenuAction(EXIT);
                    break;

                default:
                    break;
                }
            }
        }
    }

    void ExecuteMenuAction(int action) {
        switch (action) {
        case FLYING_DANGER:
            LaunchGameAndWait("bin/FlyingDanger.exe");
            break;

        case CANDY_RAIN:
            LaunchGameAndWait("bin/CandyRain.exe");
            break;

        case BIZZARE_UNDERGROUND:
            LaunchGameAndWait("bin/BizzareUnderground.exe");
            break;

        case ABOUT:
            ShowAboutWindow();
            break;

        case EXIT:
            window.close();
            break;

        default:
            break;
        }
    }

    void LaunchGameAndWait(const std::string& gamePath) {
        window.setVisible(false); // Прячем окно лаунчера

        HANDLE gameProcess = GameLauncher::LaunchGame(gamePath);
        GameLauncher::WaitForGameExit(gameProcess);

        window.setVisible(true); // Показываем окно обратно
    }

    void ShowAboutWindow() {
        // Создаём окно "Об авторах"
        sf::RenderWindow aboutWindow(sf::VideoMode(800, 400),
            "Об авторах", sf::Style::Close);
        aboutWindow.setFramerateLimit(60);

        sf::Text aboutTitle;
        aboutTitle.setFont(font);
        aboutTitle.setString("Об авторах");
        aboutTitle.setCharacterSize(50);
        aboutTitle.setFillColor(sf::Color::White);
        aboutTitle.setPosition(150, 30);

        sf::Text aboutContent;
        aboutContent.setFont(font);
        aboutContent.setString(
            "Курсовой проект: Игровой Лаунчер\n\n"
            "Flying Danger - Автор 1\n"
            "Candy Rain - Автор 2\n"
            "Bizzare Underground - Автор 3\n\n"
            "Лаунчер разработан для интеграции мини-игр\n\n"
            "Нажмите любую клавишу для закрытия..."
        );
        aboutContent.setFont(font);
        aboutContent.setCharacterSize(20);
        aboutContent.setFillColor(sf::Color(200, 200, 200));
        aboutContent.setPosition(50, 120);

        // Цикл отображения
        while (aboutWindow.isOpen()) {
            sf::Event event;
            while (aboutWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed ||
                    event.type == sf::Event::KeyPressed) {
                    aboutWindow.close();
                }
            }

            aboutWindow.clear(sf::Color(50, 50, 50));
            aboutWindow.draw(aboutTitle);
            aboutWindow.draw(aboutContent);
            aboutWindow.display();
        }
    }

    void Update() {
        hoverBobbing += bobSpeed;
    }

    void Draw() {
        window.clear(sf::Color(30, 30, 40)); // Тёмный фон

        // Рисуем заголовок
        window.draw(title);

        // Рисуем элементы меню с анимацией
        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (i == selectedIndex) {
                // Добавляем лёгкую анимацию к выбранному элементу
                float bobOffset = std::sin(hoverBobbing) * 5.f;
                sf::Vector2f pos = menuItems[i].getPosition();
                menuItems[i].setPosition(pos.x + 20.f + bobOffset, pos.y);
            }
            window.draw(menuItems[i]);

            // Возвращаем позицию для следующего кадра
            if (i == selectedIndex) {
                sf::Vector2f pos = menuItems[i].getPosition();
                menuItems[i].setPosition(pos.x - 20.f, pos.y);
            }
        }

        // Рисуем подсказку внизу
        sf::Text hint;
        hint.setFont(font);
        hint.setString("Используй UP/DOWN для выбора, ENTER для запуска, ESC для выхода");
        hint.setCharacterSize(14);
        hint.setFillColor(sf::Color(150, 150, 150));
        hint.setPosition(50, 720);
        window.draw(hint);

        window.display();
    }

    void Run() {
        while (window.isOpen()) {
            HandleInput();
            Update();
            Draw();
        }
    }

    ~MainMenu() = default;
};

int main() {
    std::cout << "=== Game Launcher запущен ===" << std::endl;

    MainMenu launcher;
    launcher.Run();

    std::cout << "=== Game Launcher завершен ===" << std::endl;
    return 0;
}