#include "CPosition.h"


CPosition::CPosition(int _x /*= 0*/, int _y /*= 0*/)
{
    x = _x;
    y = _y;
}

CPosition::~CPosition()
{

}

CPosition CPosition::operator=(CPosition _pos)
{
    x = _pos.x;
    y = _pos.y;

    return *this;
}

CPosition CPosition::operator+(CPosition _pos)
{
    CPosition tmpPos = CPosition(0, 0);
    tmpPos.x = this->x + _pos.x;
    tmpPos.y = this->y + _pos.y;

    return tmpPos;
}

CPosition CPosition::operator + (CDirection _direction)
{
    CPosition tmpPos = *this;
    switch (_direction)
    {
    case DI_UP:    {tmpPos.x -= 1;  break; }
    case DI_DOWN:  {tmpPos.x += 1;  break; }
    case DI_RIGHT: {tmpPos.y += 1;  break; }
    case DI_LEFT:  {tmpPos.y -= 1;  break; }
    default:  break;
    }

    return tmpPos;
}

float CPosition::operator-(CPosition _pos)
{
    return float(sqrt ((x - _pos.x)*(x - _pos.x) + (y - _pos.y)*(y - _pos.y)));
}

int CPosition::getX()
{
    return x;
}

int CPosition::getY()
{
    return y;
}

void CPosition::setX(int _x)
{
    x = _x;
}

void CPosition::setY(int _y)
{
    y = _y;
}

bool CPosition::operator==(CPosition _pos)
{
    return x == _pos.x&&y == _pos.y;
}


bool operator<(CPosition _pos1, CPosition _pos2)
{
    if (_pos1.x < _pos2.x)
    {
        return true;
    }
    else if (_pos1.x > _pos2.x)
    {
        return false;
    }
    else
    {
        if (_pos1.y < _pos2.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
