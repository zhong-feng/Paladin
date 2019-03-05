#pragma once
#include "bagData.h"
#include "CRole.h"

class CItem
{
public:
    CItem();
    ~CItem();

    //使用物品
    virtual void useItem(CRole* _role);

    //卸下装备
    virtual void putDownEquipment(CRole* _role);

    //打印 图标
    virtual void renderItem(CPosition _pos);

    //打印信息
    virtual void renderItemInfo(CPosition _pos);

public:
    CItemID id;
    CItemType type;

    string name;        //物品名字
    string description; //物品描述

    int count;  //可叠加存放的数量

    int buyPrice;
    int sellPrice;
};

