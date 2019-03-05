#include "CBag.h"

#include "CTaskDirector.h"

map<CPosition, CBagUnit*>::iterator CBag::findFirstEmpty()
{
    auto tmpItr = m_logicBag.begin();

    for (; tmpItr != m_logicBag.end(); tmpItr++)
    {
        if (tmpItr->second->isEmpty())
        {
            break;
        }
    }

    return tmpItr;
}

map<CPosition, CBagUnit*>::iterator CBag::findUnitByItemID(CItemID _id)
{
    auto tmpItr = m_logicBag.begin();

    for (; tmpItr != m_logicBag.end(); tmpItr++)
    {
        if (tmpItr->second->getID() == _id
            && tmpItr->second->isFull() == false)
        {
            break;
        }
    }

    return tmpItr;
}

void CBag::onInit()
{
    //创建背包中的逻辑单元格, 与背包界面对应
    for (int i = 1; i < row - 1; i++)
    {
        for (int j = 1; j < col - 1; j++)
        {
            CBagUnit* pTmpBagUnit = new CBagUnit();
            m_logicBag.insert(make_pair(CPosition(i, j), pTmpBagUnit));
        }
    }
}

void CBag::showFull()
{
    CUtils::setColor(79);
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX, BAGPROMPTPOSY));
    cout << "                           ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY));
    cout << "      背包已满，添加失败   ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY));
    cout << "      按任意键继续         ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 3, BAGPROMPTPOSY));
    cout << "                           ";

    _getch();

    CUtils::setColor();
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX, BAGPROMPTPOSY));
    cout << "                           ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY));
    cout << "                           ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY));
    cout << "                           ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 3, BAGPROMPTPOSY));
    cout << "                           ";
}

CBagUnit* CBag::getBagUnit(CPosition pos)
{
    if (m_logicBag.count(pos) == 1)
    {
        return m_logicBag[pos];
    }

    return nullptr;
}

CItemID CBag::useItem(CPosition pos, int _num /*= 1*/)
{
    //确定单元格存在
    if (m_logicBag.count(pos) == 1)
    {
        //确认存放的物品可以被使用
        auto tmpID = m_logicBag[pos]->getID();
        auto tmpItem = CItemFactory::createItem(tmpID);

        //只有 药品 武器 衣服 可以被使用
        if (tmpItem->type != IT_Drug
            && tmpItem->type != IT_Weapon
            && tmpItem->type != IT_Garment)
        {
            delete tmpItem;
            tmpItem = 0;

            return ID_None;
        }

        //判断数量不够,直接返回
        if (m_logicBag[pos]->getCount() < _num)
        {
            delete tmpItem;
            tmpItem = 0;

            return ID_None;
        }
        else
        {
            //物品数量足够, 数量减少,
            auto tmpItemCount = m_logicBag[pos]->getCount() - _num;

            m_logicBag[pos]->setCount(tmpItemCount);

            //当前物品单元格的物品数量为0 , 清空 背包单元格
            if (tmpItemCount == 0)
            {
                m_logicBag[pos]->setID(ID_None);
            }

            delete tmpItem;
            tmpItem = 0;

            return tmpID;
        }
    }

    return ID_None;
}

bool CBag::addItem(CItemID _id, int _num /*= 1*/)
{
    //确定结束条件
    if (_num == 0)
    {
        return true;
    }

    //1. 看是否已有同 ID 且不满的单元格 
    auto tmpFindID = findUnitByItemID(_id);

    if (tmpFindID == m_logicBag.end())
    {
        //没有符合要求的单元格 找到 到第一个空的单元格
        auto tmpFirstEmpty = findFirstEmpty();

        if (tmpFirstEmpty == m_logicBag.end())
        {
            //背包装满了
            showFull();

            return false;
        }

        //确定背包单元格 
        auto tmpUnit = tmpFirstEmpty->second;

        //将一个物品放入对应的单元格中
        tmpUnit->setID(_id);
        tmpUnit->setCount(1);

        //添加物品 触发收集物品的任务
        doTaskOfCollect(_id);

        //继续添加剩余的 数量
        return  addItem(_id, _num - 1);
    }
    else
    {
        //确定背包单元格 
        auto tmpUnit = tmpFindID->second;

        //将一个物品放入对应的单元格中 (count++)
        tmpUnit->setCount(tmpUnit->getCount() + 1);

        //添加物品 触发收集物品的任务
        doTaskOfCollect(_id);

        //继续添加剩余的 数量
        return  addItem(_id, _num - 1);
    }
}

void CBag::renderBagUI(CPosition renderPt)
{
    //依次打印背包
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //先打印背包边框
            if ((i == 0 || i == row - 1) || (j == 0 || j == col - 1))
            {
                //定位要打印的 地方
                CUtils::gotoXY(renderPt.getX() + i, (renderPt.getY() + j) * 2);

                CUtils::setColor(64);
                cout << "◆";
                CUtils::setColor();
            }
            else
            {
                //后打印背包单元格
                if (m_logicBag.count(CPosition(i, j)) == 1)  //判断键值对是否存在
                {
                    auto pBagUnit = m_logicBag[CPosition(i, j)];
                    auto itemId = pBagUnit->getID();
                    auto go = CItemFactory::createItem(itemId);

                    //打印物品
                    go->renderItem(renderPt + CPosition(i, j));

                    delete go;
                    go = 0;
                }
            }
        }
    }
}

CBag::~CBag()
{
    if (row != 0 && col != 0)
    {
        for (int i = 1; i < row - 1; i++)
        {
            for (int j = 1; j < col - 1; j++)
            {
                if (m_logicBag.find(CPosition(i, j)) != m_logicBag.end())
                {
                    if (m_logicBag[CPosition(i, j)])
                    {
                        delete m_logicBag[CPosition(i, j)];
                        m_logicBag[CPosition(i, j)] = 0;
                    }
                }
            }
        }
    }
}

CBag::CBag()
{
    //给背包赋初值
    col = COLOFBAG;
    row = ROLOFBAG;

    //给背包赋初值
    onInit();
}

int CBag::getCountItemID(CItemID _id)
{
    auto tmpItr = m_logicBag.begin();

    for (; tmpItr != m_logicBag.end(); tmpItr++)
    {
        if (tmpItr->second->getID() == _id)
        {
            return tmpItr->second->getCount();
        }
    }

    return 0;
}

void CBag::doTaskOfCollect(CItemID _id)
{
    auto taskList = CTaskDirector::getInstance()->getTaskList();

    for (auto itr = (*taskList).begin(); itr != (*taskList).end(); itr++)
    {
        //收集任务才需要查看物品
        if ((*itr)->taskType == TT_Collect && (*itr)->itemID == _id)
        {
            (*itr)->itemCount++;

            if ((*itr)->itemCount >= (*itr)->itemMax)
            {
                (*itr)->taskMode = MODEFINISED;
            }

        }
    }
}

bool CBag::giveItemToTask(CItemID _id, int _num)
{
    for (auto element : m_logicBag)
    {
        auto tmpBagUnit = element.second;

        if (tmpBagUnit->getID() == _id)
        {
            //确定 已有物品数量
            int tmpNum = tmpBagUnit->getCount();

            if (tmpNum < _num)
            {
                return false;
            }

            tmpBagUnit->setCount(tmpNum - _num);

            if (tmpBagUnit->getCount() == 0)
            {
                tmpBagUnit->setID(ID_None);
            }

        }
    }

    return true;
}
