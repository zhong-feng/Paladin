#include "CSackcloth.h"

void CSackcloth::putDownEquipment(CRole* _role)
{
    _role->setBasicDefence(_role->getBasicDefence() - defence);
    _role->setAgility(_role->getAgility() - agility);

    _role->initDataForAttribute();
}

void CSackcloth::useItem(CRole* _role)
{
    _role->setBasicDefence(_role->getBasicDefence() + defence);
    _role->setAgility(_role->getAgility() + agility);

    _role->initDataForAttribute();
}

void CSackcloth::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << name;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "防御力  +" << defence;

    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "敏捷    +" << agility;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + CPosition(2, 0));
    cout << "回收价  " << sellPrice;
}

void CSackcloth::renderItem(CPosition _pos)
{
    CUtils::setColor(224);
    CUtils::gotoXY(_pos);
    cout << "* ";

    CUtils::setColor();
}

CSackcloth::~CSackcloth()
{

}

CSackcloth::CSackcloth()
{
    id = ID_Sackcloth;
}
