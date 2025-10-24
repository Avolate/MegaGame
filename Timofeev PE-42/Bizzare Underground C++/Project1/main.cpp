#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.h"
#include "Character.h"
#include "WallBlock.h"
#include "Spike.h"
#include "Box.h"
#include "Button.h"
#include "Key.h"
#include "Door.h"

int main() {
    std::cout << "--- Initialization ---" << std::endl;
    Game game;
    Character player;
    WallBlock wall;
    Spike spike;
    Box box;
    Button button;
    Key key;
    Door door;

    std::vector<Key*> keyPointers; // Для управления памятью
    const int totalKeys = 3;

    std::cout << "\n--- Creating " << totalKeys << " Keys (Dynamic Array) ---" << std::endl;
    for (int i = 0; i < totalKeys; ++i) {
        Key* newKeyPtr = new Key();
        keyPointers.push_back(newKeyPtr); // Сохраняем указатель для последующего удаления
    }

    std::cout << "--- Simulating Key Collection ---" << std::endl;

    int keysCollected = door.getKeyCounter();

    // Проходимся по вектору указателей
    // Мы будем собирать ключи, пока они есть в инвентаре
    while (!keyPointers.empty()) {
        Key* currentKeyPtr = keyPointers.back(); // Получаем указатель на последний ключ
        keyPointers.pop_back(); // Удаляем указатель из вектора

        // Используем указатель для доступа к членам:
        if (currentKeyPtr->characterKeyContact(player.getPositionX(), player.getPositionY())) {
            keysCollected = currentKeyPtr->keyDestroy(keysCollected);
        }

        //удаляем объект из памяти, который мы создали через new
        delete currentKeyPtr;
    }

    door.setKeyCounter(keysCollected);
    std::cout << "Total keys collected: " << door.getKeyCounter() << std::endl;

    std::cout << "\n--- Game Actions ---" << std::endl;

    // 1. Действия персонажа
    player.movementRight();
    player.jump();
    player.fallingCharacter();

    // 2. Изменения на карте
    wall.putingWall();
    spike.putingSpike();

    // 3. Проверка коллизий
    spike.characterSpikeContact(player.getPositionX(), player.getPositionY()); 
    box.characterBoxContact(player.getPositionX(), player.getPositionY());
    button.characterButtonContact(player.getPositionX(), player.getPositionY());
    key.characterKeyContact(player.getPositionX(), player.getPositionY());

    // 4. Логика кнопки (при условии, что кнопка нажата)
    if (button.getIsPressed()) {  
        button.buttonChanges(wall.getIsHide(), spike.getIsHide());  
    }

    // 5. Проверка дверей на ключи
    int currentKeys = key.keyDestroy(door.getKeyCounter()); 
    door.setKeyCounter(currentKeys);   
    door.doorOpen();

    // 6. Игровой цикл фрагмента
    game.win(player.getPositionX(), player.getPositionY());

    std::cout << "\n--- End Simulation ---" << std::endl;

    return 0;
}