#pragma once
#include "CDrug.h"
class CHP : public CDrug
{
public:
    CHP();
    ~CHP();

    //��д��ӡ ͼ��
    void renderItem(CPosition _pos) override;

    //��д��ӡ��Ϣ ����
    void renderItemInfo(CPosition _pos)override;

    //ʹ����Ʒ
    void useItem(CRole* _role)override;


};

