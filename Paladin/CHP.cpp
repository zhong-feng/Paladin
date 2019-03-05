#include "CHP.h"


void CHP::useItem(CRole* _role)
{
    _role->setCurHP(_role->getCurHP() + hp);

    //判断边界
    if (_role->getCurHP() > _role->getMaxHP())
    {
        _role->setCurHP(_role->getMaxHP());
    }
}

void CHP::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + DI_DOWN);
    cout << "HP  +" << hp;

    CUtils::gotoXY(_pos+CPosition(3,0));
    cout << "回收价  " << sellPrice;
}

void CHP::renderItem(CPosition _pos)
{
    CUtils::setColor(32);
    CUtils::gotoXY(_pos);
    cout << "@ ";

    CUtils::setColor();
}

CHP::~CHP()
{
    
}

CHP::CHP()
{
    id = ID_HP;
}
