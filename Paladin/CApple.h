#pragma once
#include "CItem.h"
class CApple :
    public CItem
{
public:
    CApple();
    ~CApple();

    //重写打印 图标
    void renderItem(CPosition _pos) override;

    //重写打印信息 方法
    void renderItemInfo(CPosition _pos)override;
};

