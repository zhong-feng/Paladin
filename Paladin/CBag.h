#pragma once
#include "CBagUnit.h"
class CBag
{
public:
    CBag();
    ~CBag();

    //背包的渲染部分 -- 根据 背包的逻辑部分 来渲染
    void renderBagUI(CPosition renderPt);

    //添加物品  (每次添加一个  递归添加)
    bool addItem(CItemID _id, int _num = 1);

    //查看物品的数量
    int getCountItemID(CItemID _id);

    //上交任务物品
    bool giveItemToTask(CItemID _id,int _num );

    //使用物品
    CItemID useItem(CPosition pos, int _num = 1);

    //查找单元格
    CBagUnit* getBagUnit(CPosition pos);

protected:
    //收集物品的任务
    void doTaskOfCollect(CItemID _id);

    //输出背包已满 提示信息
    void showFull();

    //背包的初始化
    void onInit();

    //查找里 物品id 相同，切没有满的单元格 (返回迭代器)
    map<CPosition, CBagUnit*>::iterator findUnitByItemID(CItemID _id);

    //找到第一个空的单元格 (返回迭代器)
    map<CPosition, CBagUnit*>::iterator findFirstEmpty();

protected:
    map<CPosition, CBagUnit*> m_logicBag;   //逻辑上的背包

    GS_SYNTHESIZE(int, row, Row);
    GS_SYNTHESIZE(int, col, Col);
};

