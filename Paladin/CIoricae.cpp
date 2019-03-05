#include "CIoricae.h"


void CIoricae::putDownEquipment(CRole* _role)
{
    _role->setBasicDefence(_role->getBasicDefence() - defence);

    _role->initDataForAttribute();
}

void CIoricae::useItem(CRole* _role)
{
    _role->setBasicDefence(_role->getBasicDefence() + defence);

    _role->initDataForAttribute();
}

void CIoricae::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << name;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "������  +" << defence;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + CPosition(2,0));
    cout << "���ռ�  " << sellPrice;
}

void CIoricae::renderItem(CPosition _pos)
{
    CUtils::setColor(224);
    CUtils::gotoXY(_pos);
    cout << "& ";

    CUtils::setColor();
}

CIoricae::~CIoricae()
{

}

CIoricae::CIoricae()
{
    id = ID_Ioricae;
}
