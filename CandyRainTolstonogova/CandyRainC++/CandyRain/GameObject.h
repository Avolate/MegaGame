#pragma once
#include <string>
class GameObject
{
private:
    int positionX;
    int positionY;
    std::string sprite;

public:
    GameObject(int x, int y, const std::string &spritepath);
    ~GameObject(); 
    // Getter
    int GetpositionX() const;
    int GetpositionY() const;
    std::string Getsprite() const;
    // Setter
    void SetpositionX(int count);
    void SetpositionY(int count);
    void Setsprite(std::string bg);
    virtual void DisplayInfo() const;
};

