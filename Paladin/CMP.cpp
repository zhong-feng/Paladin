#include "CMP.h"


void CMP::useItem(CRole* _role)
{
    _role->setCurMP(_role->getCurMP() + hp);

    //�жϱ߽�
    if (_role->getCurMP() > _role->getMaxMP())
    {
        _role->setCurMP(_role->getMaxMP());
    }
}

void CMP::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + DI_DOWN);
    cout << "MP  +" << mp;

    CUtils::gotoXY(_pos + CPosition(3, 0));
    cout << "���ռ�  " << sellPrice;
}

void CMP::renderItem(CPosition _pos)
{
    CUtils::setColor(32);
    CUtils::gotoXY(_pos);
    cout << "# ";

    CUtils::setColor();
}

CMP::~CMP()
{
    
}

CMP::CMP()
{
    id = ID_MP;
}
