#include "CApple.h"


void CApple::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << name;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos );
    cout << description;

    CUtils::gotoXY(_pos + DI_DOWN);
    cout << "不可使用";

    CUtils::gotoXY(_pos + CPosition(3, 0));
    cout << "回收价  " << sellPrice;

}

void CApple::renderItem(CPosition _pos)
{
    CUtils::setColor(144);
    CUtils::gotoXY(_pos);
    cout << "^ ";

    CUtils::setColor();
}

CApple::~CApple()
{

}

CApple::CApple()
{
    id = ID_Apple;
    type = IT_Task;
    count = 99;
}
