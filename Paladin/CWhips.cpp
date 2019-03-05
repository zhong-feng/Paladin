#include "CWhips.h"


void CWhips::putDownEquipment(CRole* _role)
{
    _role->setBasicAttack(_role->getBasicAttack() - attack);
    _role->setIntelligence(_role->getIntelligence() - intelligence);

    _role->initDataForAttribute();

    if (_role->getCurMP() > _role->getMaxMP())
    {
        _role->setCurMP(_role->getMaxMP());
    }
}

void CWhips::useItem(CRole* _role)
{
    _role->setBasicAttack(_role->getBasicAttack() + attack);
    _role->setIntelligence(_role->getIntelligence() + intelligence);

    _role->initDataForAttribute();
}

void CWhips::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << name;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "攻击力  +" << attack;

    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << "智力    +" << intelligence;

    _pos = _pos + DI_DOWN;
    _pos = _pos + DI_DOWN;
    CUtils::gotoXY(_pos);
    cout << description;

    CUtils::gotoXY(_pos + CPosition(2, 0));
    cout << "回收价  " << sellPrice;
}

void CWhips::renderItem(CPosition _pos)
{
    CUtils::setColor(236);
    CUtils::gotoXY(_pos);
    cout << "% ";

    CUtils::setColor();
}

CWhips::~CWhips()
{

}

CWhips::CWhips()
{
    id = ID_Whips;
}
