#pragma once
#include "CDrug.h"
class CMP :
    public CDrug
{
public:
    CMP();
    ~CMP();


    //��д��ӡ ͼ��
    void renderItem(CPosition _pos) override;

    //��д��ӡ��Ϣ ����
    void renderItemInfo(CPosition _pos)override;

    //ʹ����Ʒ
    void useItem(CRole* _role)override;



};

