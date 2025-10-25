#include <windows.h>
#include <iostream>
#include "GameMain.h"
#include "Player.h"
#include "Sweet.h"
#include "Heart.h"
#include "Trash.h"
#include "Sweets_distribution.h"

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int health = 3;
    GameMain game(health, "back_ground.png", "paused");
    game.start();
    srand(time(nullptr));
    int candycount = Sweets_distribution::countCandyChoice();
    int donutcount = Sweets_distribution::countDonutChoice();
    int cakecount = Sweets_distribution::countCakeChoice();
    const int trashcount = Sweets_distribution::countTrashChoice();

    //статическая инициализация
    Player sweetTooth(rand() % GameMain::maxfloorX + 1, GameMain::floorY, "player.png", 2, true);
    sweetTooth.displayInfo();

    //динамическая инициализация объектов
    Heart* fallheart = new Heart(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "heart.png", rand() % GameMain::maxspeed + 1, 5, false, false);
    fallheart->displayInfo();
    fallheart->plusHealth(health);
    const int size = 3;
    //динамический массив объектов
    Sweet* sweet = new Sweet[size]
    {
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "candy.png", rand() % GameMain::maxspeed + 1, 1, false, false),
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "kake.png", rand() % GameMain::maxspeed + 1, 2, false, false),
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "donut.png",rand() % GameMain::maxspeed + 1, 3, false, false)
    };
    for (int i = 0; i < size; i++) {
        sweet[i].displayInfo();
    }
    //массив динамических объектов
    Trash* ArTrash[size];
    for (int i = 0; i < size; i++) {
        ArTrash[i] = new Trash(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "trash.png", rand() % GameMain::maxspeed + 1, 4, false, false);
        ArTrash[i]->displayInfo();
    }
    sweetTooth.moveRight();
    int player_x = 30;
    int player_y = 5;
    for (int i = 0; i < size; i++) {
        sweet[i].falling();
        sweet[i].playerCatchSweet(player_x, player_y);
        sweet[i].sweetTouchFloor();
        ArTrash[i]->falling();
        ArTrash[i]->playerCatchTrash(player_x, player_y);
    }
    sweet[2].changeCandy(candycount);
    sweet[1].minusHealth(health);
    game.winCheck(candycount, cakecount, donutcount);
    game.loseCheck();

    delete[] sweet;
    for (int i = 0; i < size; i++) {
        delete ArTrash[i];
    }
}
 /*  for (int i = 0; i < candycount; ++i) {
       sweet[i].setnumb(1);
       std::cout << "sweet[" << i << "].x = " << sweet[i].getpositionX() << std::endl;
       std::cout << "sweet[" << i << "].setnumb(1) = " << sweet[i].getnumb() << std::endl;
       sweet[i].setsprite("candy.png");
       std::cout << "sweet[" << i << "].setsprite() = " << sweet[i].getsprite() << std::endl;
   }
   for (int i = candycount; i < size-cakecount; ++i) {
       sweet[i].setnumb(2);
       std::cout << "sweet[" << i << "].x = " << sweet[i].getpositionX() << std::endl;
       std::cout << "sweet[" << i << "].setnumb(1) = " << sweet[i].getnumb() << std::endl;
       sweet[i].setsprite("donut.png");
       std::cout << "sweet[" << i << "].setsprite() = " << sweet[i].getsprite() << std::endl;
   }
   for (int i = size - cakecount; i < size; ++i) {
       sweet[i].setnumb(3);
       std::cout << "sweet[" << i << "].x = " << sweet[i].getpositionX() << std::endl;
       std::cout << "sweet[" << i << "].setnumb(1) = " << sweet[i].getnumb() << std::endl;
       sweet[i].setsprite("cake.png");
       std::cout << "sweet[" << i << "].setsprite() = " << sweet[i].getsprite() << std::endl;

   }*/
   
