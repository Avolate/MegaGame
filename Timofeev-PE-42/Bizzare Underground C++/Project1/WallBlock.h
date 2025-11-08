#pragma once
#include "GameObject.h"

class WallBlock : public GameObject {
private:
    bool isHide;

public:
    WallBlock();
    ~WallBlock();

    void putingWall();

    // Getter
    bool getIsHide() const;

    // Setter
    void setIsHide(bool hide);
};
 