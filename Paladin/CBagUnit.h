#pragma once
#include "CItemFactory.h"

class CBagUnit
{
public:
    CBagUnit();
    ~CBagUnit();

    //判断单元格是否为空
    bool isEmpty();

    //判断单元格是否已满
    bool isFull();

    //可存放 最大 数量
    int getCapacaty();

protected:
    GS_SYNTHESIZE(CItemID, id, ID);
    GS_SYNTHESIZE(int, count, Count);

};

