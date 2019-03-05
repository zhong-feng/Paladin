#pragma once
#include "bagData.h"
#include "CRole.h"

class CItem
{
public:
    CItem();
    ~CItem();

    //ʹ����Ʒ
    virtual void useItem(CRole* _role);

    //ж��װ��
    virtual void putDownEquipment(CRole* _role);

    //��ӡ ͼ��
    virtual void renderItem(CPosition _pos);

    //��ӡ��Ϣ
    virtual void renderItemInfo(CPosition _pos);

public:
    CItemID id;
    CItemType type;

    string name;        //��Ʒ����
    string description; //��Ʒ����

    int count;  //�ɵ��Ӵ�ŵ�����

    int buyPrice;
    int sellPrice;
};

