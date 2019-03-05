#include "CBagUnit.h"


int CBagUnit::getCapacaty()
{
    //先判断是否为空
    if (isEmpty())
    {
        //默认存无限个 （999）
        return 999;
    }

    //有物品时  确定可叠加数量
    int maxCount = 0;

    CItem* pTmpItem = CItemFactory::createItem(id);
    if (pTmpItem)
    {
        //确定可叠加数量
        maxCount = pTmpItem->count;

        //手动释放数据
        delete pTmpItem;
        pTmpItem = 0;
    }
    else
    {
        maxCount = 999;
    }

    return maxCount;
}

bool CBagUnit::isFull()
{
    return count == getCapacaty();
}

bool CBagUnit::isEmpty()
{
    return count == 0;
}

CBagUnit::~CBagUnit()
{

}

CBagUnit::CBagUnit()
{
    id = ID_None;
    count = 0;
}
