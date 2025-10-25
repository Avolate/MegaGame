#include "FallingObject.h"
#include <iostream> 
#include "GameMain.h"
FallingObject::FallingObject(int x, int y,  std::string spritepath, int spd, int num, bool ptouch, bool ftouch) :
    GameObject(x, y,  spritepath), speed(spd), numb(num), player_touch(ptouch), floor_touch(ftouch) {
    std::cout << "Объект FallingObject создан" << std::endl;
}

FallingObject::~FallingObject() {
    std::cout << "Объект FallingObject уничтожен" << std::endl;
}
void FallingObject::Falling() {
    int new_position = GetpositionY();
    new_position -= speed;
    SetpositionY(new_position);
    std::cout << Getsprite() <<" падает.Новая позиция Y :" << GetpositionY() << std::endl;

}

void FallingObject::MinusHealth(int &health) {
    if (health > 0) {
        health-=1;
        std::cout << "Здоровье уменьшено. Текущее здоровье: " << health << std::endl;
    }
}
void FallingObject::DisplayInfo() {
    std::cout << "FallingObject: X=" << GetpositionX() << ", Y=" << GetpositionY()
        << ", Speed=" << speed << ", Number=" << numb
        << std::endl;
}

// Getter
int FallingObject::Getnumb() const { return numb; }
bool FallingObject::Getplayertouch() const { return player_touch; }
bool FallingObject::Getfloortouch() const { return floor_touch; }

// Setter
void FallingObject::Setnumb(int count) { numb = count; }
void FallingObject::Setplayertouch(bool count) { player_touch = count; }
void FallingObject::Setfloortouch(bool count) { floor_touch = count; }

