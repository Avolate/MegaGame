#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class GameLauncher {
public:
    static HANDLE LaunchGame(const std::string& gamePath);
    static void WaitForGameExit(HANDLE gameProcess);
};

HANDLE GameLauncher::LaunchGame(const std::string& gamePath) {
    STARTUPINFOA si = {};
    PROCESS_INFORMATION pi = {};
    si.cb = sizeof(si);

    char fullPath[MAX_PATH];
    GetFullPathNameA(gamePath.c_str(), MAX_PATH, fullPath, nullptr);

    std::cout << "Starting game: " << fullPath << std::endl;

    if (CreateProcessA(
        fullPath,
        nullptr,
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    )) {
        std::cout << "Game started successfully! PID: " << pi.dwProcessId << std::endl;
        CloseHandle(pi.hThread);
        return pi.hProcess;
    }
    else {
        DWORD error = GetLastError();
        std::cerr << "Error starting game. Code: " << error << std::endl;
        return nullptr;
    }
}

void GameLauncher::WaitForGameExit(HANDLE gameProcess) {
    if (gameProcess) {
        std::cout << "Waiting for game to exit..." << std::endl;
        WaitForSingleObject(gameProcess, INFINITE);
        CloseHandle(gameProcess);
        std::cout << "Game exited, returning to menu" << std::endl;
    }
}

class MainMenu {
private:
    enum MenuItem {
        FLYING_DANGER = 0,
        CANDY_RAIN = 1,
        BIZZARE_UNDERGROUND = 2,
        ABOUT = 3,
        EXIT = 4
    };

    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int selectedIndex;
    const int ITEM_COUNT = 5;

    sf::Color colorSelected;
    sf::Color colorUnselected;

    float hoverBobbing;
    float bobSpeed;

public:
    MainMenu() : window(sf::VideoMode(1024, 768), "Game Launcher", sf::Style::Close),
        selectedIndex(0),
        colorSelected(100, 200, 255),
        colorUnselected(200, 200, 200),
        hoverBobbing(0.f),
        bobSpeed(0.05f)
    {
        window.setFramerateLimit(60);

        if (!font.loadFromFile("resources/fonts/arial.ttf")) {
            if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
                std::cerr << "ERROR: Could not load font!" << std::endl;
            }
        }

        InitializeMenu();
    }

    void InitializeMenu() {
        title.setFont(font);
        title.setString("GAME LAUNCHER");
        title.setCharacterSize(60);
        title.setFillColor(sf::Color::White);

        float titleX = (window.getSize().x - title.getLocalBounds().width) / 2.f;
        title.setPosition(titleX, 50.f);

        std::vector<std::string> itemNames = {
            "1. Flying Danger",
            "2. Candy Rain",
            "3. Bizzare Underground",
            "4. About",
            "5. Exit"
        };

        float startY = 200.f;
        float itemSpacing = 80.f;

        for (size_t i = 0; i < itemNames.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(itemNames[i]);
            item.setCharacterSize(40);
            item.setFillColor(colorUnselected);

            float itemX = (window.getSize().x - item.getLocalBounds().width) / 2.f;
            item.setPosition(itemX, startY + i * itemSpacing);

            menuItems.push_back(item);
        }

        UpdateMenuSelection();
    }

    void UpdateMenuSelection() {
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
            LaunchGameAndWait("bin/FlyingDangerC++.exe");
            break;
        case CANDY_RAIN:
            LaunchGameAndWait("bin/CandyRainC++.exe");
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
        window.setVisible(false);
        HANDLE gameProcess = GameLauncher::LaunchGame(gamePath);
        GameLauncher::WaitForGameExit(gameProcess);
        window.setVisible(true);
    }

    void ShowAboutWindow() {
        sf::RenderWindow aboutWindow(sf::VideoMode(800, 400),
            "About", sf::Style::Close);
        aboutWindow.setFramerateLimit(60);

        sf::Text aboutTitle;
        aboutTitle.setFont(font);
        aboutTitle.setString("About Authors");
        aboutTitle.setCharacterSize(50);
        aboutTitle.setFillColor(sf::Color::White);
        aboutTitle.setPosition(150, 30);

        sf::Text aboutContent;
        aboutContent.setFont(font);
        aboutContent.setString(
            "Course Project: Game Launcher\n\n"
            "Flying Danger - Yaroslav Sychev\n"
            "Candy Rain - Elizaveta Tolstonogova\n"
            "Bizzare Underground - Arseniy Timofeev\n\n"
            "Launcher for mini-game integration\n\n"
            "Press any key to close..."
        );
        aboutContent.setFont(font);
        aboutContent.setCharacterSize(20);
        aboutContent.setFillColor(sf::Color(200, 200, 200));
        aboutContent.setPosition(50, 120);

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
        window.clear(sf::Color(30, 30, 40));
        window.draw(title);

        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (i == selectedIndex) {
                float bobOffset = std::sin(hoverBobbing) * 5.f;
                sf::Vector2f pos = menuItems[i].getPosition();
                menuItems[i].setPosition(pos.x + 20.f + bobOffset, pos.y);
            }
            window.draw(menuItems[i]);

            if (i == selectedIndex) {
                sf::Vector2f pos = menuItems[i].getPosition();
                menuItems[i].setPosition(pos.x - 20.f, pos.y);
            }
        }

        sf::Text hint;
        hint.setFont(font);
        hint.setString("UP/DOWN to select | ENTER to start | ESC to exit");
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

    ~MainMenu() {}
};

int main() {
    std::cout << "Game Launcher started" << std::endl;

    MainMenu launcher;
    launcher.Run();

    std::cout << "Game Launcher closed" << std::endl;
    return 0;
}
