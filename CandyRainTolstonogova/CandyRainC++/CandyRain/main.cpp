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
    game.Start();
    srand(time(nullptr));
    int candycount = SweetsDistribution::CountCandyChoice();
    int donutcount = SweetsDistribution::CountDonutChoice();
    int cakecount = SweetsDistribution::CountCakeChoice();
    const int trashcount = SweetsDistribution::CountTrashChoice();

    //статическая инициализация
    Player sweetTooth(rand() % GameMain::maxfloorX + 1, GameMain::floorY, "player.png", 2, true);
    sweetTooth.DisplayInfo();
    int candynum = 1;
    int donutnum = 2;
    int cakenum = 3;
    const int trashnum =4;
    int heartnum = 5;
    //динамическая инициализация объектов
    Heart* fallheart = new Heart(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "heart.png", rand() % GameMain::maxspeed + 1, heartnum, false, false);
    fallheart->DisplayInfo();
    fallheart->PlusHealth(health);
    const int size = 3;
    //динамический массив объектов
    Sweet* sweet = new Sweet[size]
    {
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "candy.png", rand() % GameMain::maxspeed + 1, candynum, false, false),
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "kake.png", rand() % GameMain::maxspeed + 1,  donutnum, false, false),
        Sweet(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "donut.png",rand() % GameMain::maxspeed + 1, cakenum, false, false)
    };
    for (int i = 0; i < size; i++) {
        sweet[i].DisplayInfo();
    }
    //массив динамических объектов
    Trash* ArTrash[size];
    for (int i = 0; i < size; i++) {
        ArTrash[i] = new Trash(rand() % GameMain::maxfloorX + 1, GameMain::maxfloorY, "trash.png", rand() % GameMain::maxspeed + 1, trashnum, false, false);
        ArTrash[i]->DisplayInfo();
    }
    sweetTooth.MoveRight();
    int player_x = 30;
    int player_y = 5;
    for (int i = 0; i < size; i++) {
        sweet[i].Falling();
        sweet[i].PLayerCatchSweet(player_x, player_y);
        sweet[i].SweetTouchFloor();
        ArTrash[i]->Falling();
        ArTrash[i]->PlayerCatchTrash(player_x, player_y);
    }
    sweet[2].ChangeCandy(candycount);
    sweet[1].MinusHealth(health);
    game.WinCheck(candycount, cakecount, donutcount);
    game.LoseCheck();

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
   
