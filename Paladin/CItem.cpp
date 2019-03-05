#include "CItem.h"

void CItem::renderItemInfo(CPosition _pos)
{
    CUtils::gotoXY(_pos);
    cout << description;
}

void CItem::renderItem(CPosition _pos)
{
    CUtils::setColor();
    CUtils::gotoXY(_pos);
    cout << "□";
}

void CItem::useItem(CRole* _role)
{

}

CItem::~CItem()
{

}

CItem::CItem()
{
    //数据置零  
    id = ID_None;
    type = IT_None;

    name = "";
    description = "空";

    //默认可存数量（假设无限个  999）
    count = 999;

    buyPrice = 0;
    sellPrice = 0;
}


void CItem::putDownEquipment(CRole* _role)
{

}
