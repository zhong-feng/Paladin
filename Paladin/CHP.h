#pragma once
#include "CDrug.h"
class CHP : public CDrug
{
public:
    CHP();
    ~CHP();

    //重写打印 图标
    void renderItem(CPosition _pos) override;

    //重写打印信息 方法
    void renderItemInfo(CPosition _pos)override;

    //使用物品
    void useItem(CRole* _role)override;


};

