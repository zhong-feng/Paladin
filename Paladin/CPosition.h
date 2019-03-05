#pragma once
#include "game.h"

class CPosition
{
public:
    CPosition(int _x = 0, int _y = 0);
    ~CPosition();

    CPosition operator=(CPosition _pos);

    bool operator==(CPosition _pos);

    CPosition operator+(CPosition _pos);

    CPosition operator+(CDirection _direction);

    //返回两点之间的距离
    float operator-(CPosition _pos);

    friend bool operator<(CPosition _pos1, CPosition _pos2);

    int getX();
    int getY();
    void setX(int _x);
    void setY(int _y);

    int x;
    int y;
};

//不作为成员函数重载
bool operator<(CPosition _pos1, CPosition _pos2);