#include "FallingObject.h"
#include <iostream> 
#include "GameMain.h"
FallingObject::FallingObject(int x, int y,  std::string sprite_path, int spd, int num, bool p_touch, bool f_touch) :
    GameObject(x, y,  sprite_path), speed(spd), numb(num), player_touch(p_touch), floor_touch(f_touch) {
    std::cout << "Объект FallingObject создан" << std::endl;
}

FallingObject::~FallingObject() {
    std::cout << "Объект FallingObject уничтожен" << std::endl;
}
void FallingObject::falling() {
    int new_position = getpositionY();
    new_position -= speed;
    setpositionY(new_position);
    std::cout << getsprite() <<" падает.Новая позиция Y :" << getpositionY() << std::endl;

}

void FallingObject::minusHealth(int &health) {
    if (health > 0) {
        health-=1;
        std::cout << "Здоровье уменьшено. Текущее здоровье: " << health << std::endl;
    }
}
void FallingObject::displayInfo() {
    std::cout << "FallingObject: X=" << getpositionX() << ", Y=" << getpositionY()
        << ", Speed=" << speed << ", Number=" << numb
        << std::endl;
}

// Getter
int FallingObject::getnumb() const { return numb; }
bool FallingObject::getplayer_touch() const { return player_touch; }
bool FallingObject::getfloor_touch() const { return floor_touch; }

// Setter
void FallingObject::setnumb(int count) { numb = count; }
void FallingObject::setplayer_touch(bool count) { player_touch = count; }
void FallingObject::setfloor_touch(bool count) { floor_touch = count; }

