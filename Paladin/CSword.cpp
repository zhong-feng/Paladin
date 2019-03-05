#include "CSword.h"

void CSword::putDownEquipment(CRole* _role)
{
    _role->setBasicAttack(_role->getBasicAttack() - attack);
    _role->setStrength(_role->getStrength() - strength);

    _role->initDataForAttribute();

    if (_role->getCurHP() > _role->getMaxHP())
    {
        _role->setCurHP(_role->getMaxHP());
    }
}

void CSword::useItem(CRole* _role)
{
    _role->setBasicAttack(_role->getBasicAttack() + attack);
    _role->setStrength(_role->getStrength() + strength);

    _role->initDataForAttribute();
}

void CSword::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << name;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "������  +" << attack;

    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "����    +" << strength;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + CPosition(2, 0));
    cout << "���ռ�  " << sellPrice;
}

void CSword::renderItem(CPosition _pos)
{
    CUtils::setColor(236);
    CUtils::gotoXY(_pos);
    cout << "$ ";

    CUtils::setColor();
}

CSword::~CSword()
{

}

CSword::CSword()
{
    id = ID_Sword;
}
