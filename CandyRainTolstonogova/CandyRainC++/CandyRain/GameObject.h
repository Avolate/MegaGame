#pragma once
#include <string>
class GameObject
{
private:
    int positionX;
    int positionY;
    std::string sprite;

public:
    GameObject(int x, int y, const std::string &sprite_path);
    ~GameObject(); 
    // Getter
    int getpositionX() const;
    int getpositionY() const;
    std::string getsprite() const;
    // Setter
    void setpositionX(int count);
    void setpositionY(int count);
    void setsprite(std::string bg);
    virtual void displayInfo() const;
};

