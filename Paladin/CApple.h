#pragma once
#include "CItem.h"
class CApple :
    public CItem
{
public:
    CApple();
    ~CApple();

    //��д��ӡ ͼ��
    void renderItem(CPosition _pos) override;

    //��д��ӡ��Ϣ ����
    void renderItemInfo(CPosition _pos)override;
};

