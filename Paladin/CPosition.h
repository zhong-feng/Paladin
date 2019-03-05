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

    //��������֮��ľ���
    float operator-(CPosition _pos);

    friend bool operator<(CPosition _pos1, CPosition _pos2);

    int getX();
    int getY();
    void setX(int _x);
    void setY(int _y);

    int x;
    int y;
};

//����Ϊ��Ա��������
bool operator<(CPosition _pos1, CPosition _pos2);