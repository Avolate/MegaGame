#pragma once
#include <string>

class GameObject {
private:
    int positionX;
    int positionY;
    std::string sprite;

public:
    GameObject();
    virtual ~GameObject();

    // Getters
    int getPositionX() const;
    int getPositionY() const;
    std::string getSprite() const;

    // Setters
    void setPositionX(int x);
    void setPositionY(int y);
    void setSprite(const std::string& s);
};
