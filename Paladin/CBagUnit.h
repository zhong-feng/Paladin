#pragma once
#include "CItemFactory.h"

class CBagUnit
{
public:
    CBagUnit();
    ~CBagUnit();

    //�жϵ�Ԫ���Ƿ�Ϊ��
    bool isEmpty();

    //�жϵ�Ԫ���Ƿ�����
    bool isFull();

    //�ɴ�� ��� ����
    int getCapacaty();

protected:
    GS_SYNTHESIZE(CItemID, id, ID);
    GS_SYNTHESIZE(int, count, Count);

};

