#pragma once
#include "CGarment.h"
class CSackcloth :
    public CGarment
{
public:
    CSackcloth();
    ~CSackcloth();


    //��д��ӡ ͼ��
    void renderItem(CPosition _pos) override;

    //��д��ӡ��Ϣ ����
    void renderItemInfo(CPosition _pos)override;

    //ʹ����Ʒ
    void useItem(CRole* _role)override;

    //жװ��
    void putDownEquipment(CRole* _role)override;


};
