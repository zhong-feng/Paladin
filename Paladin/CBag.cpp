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
    //���������е��߼���Ԫ��, �뱳�������Ӧ
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
    cout << "      �������������ʧ��   ";
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY));
    cout << "      �����������         ";
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
    //ȷ����Ԫ�����
    if (m_logicBag.count(pos) == 1)
    {
        //ȷ�ϴ�ŵ���Ʒ���Ա�ʹ��
        auto tmpID = m_logicBag[pos]->getID();
        auto tmpItem = CItemFactory::createItem(tmpID);

        //ֻ�� ҩƷ ���� �·� ���Ա�ʹ��
        if (tmpItem->type != IT_Drug
            && tmpItem->type != IT_Weapon
            && tmpItem->type != IT_Garment)
        {
            delete tmpItem;
            tmpItem = 0;

            return ID_None;
        }

        //�ж���������,ֱ�ӷ���
        if (m_logicBag[pos]->getCount() < _num)
        {
            delete tmpItem;
            tmpItem = 0;

            return ID_None;
        }
        else
        {
            //��Ʒ�����㹻, ��������,
            auto tmpItemCount = m_logicBag[pos]->getCount() - _num;

            m_logicBag[pos]->setCount(tmpItemCount);

            //��ǰ��Ʒ��Ԫ�����Ʒ����Ϊ0 , ��� ������Ԫ��
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
    //ȷ����������
    if (_num == 0)
    {
        return true;
    }

    //1. ���Ƿ�����ͬ ID �Ҳ����ĵ�Ԫ�� 
    auto tmpFindID = findUnitByItemID(_id);

    if (tmpFindID == m_logicBag.end())
    {
        //û�з���Ҫ��ĵ�Ԫ�� �ҵ� ����һ���յĵ�Ԫ��
        auto tmpFirstEmpty = findFirstEmpty();

        if (tmpFirstEmpty == m_logicBag.end())
        {
            //����װ����
            showFull();

            return false;
        }

        //ȷ��������Ԫ�� 
        auto tmpUnit = tmpFirstEmpty->second;

        //��һ����Ʒ�����Ӧ�ĵ�Ԫ����
        tmpUnit->setID(_id);
        tmpUnit->setCount(1);

        //�����Ʒ �����ռ���Ʒ������
        doTaskOfCollect(_id);

        //�������ʣ��� ����
        return  addItem(_id, _num - 1);
    }
    else
    {
        //ȷ��������Ԫ�� 
        auto tmpUnit = tmpFindID->second;

        //��һ����Ʒ�����Ӧ�ĵ�Ԫ���� (count++)
        tmpUnit->setCount(tmpUnit->getCount() + 1);

        //�����Ʒ �����ռ���Ʒ������
        doTaskOfCollect(_id);

        //�������ʣ��� ����
        return  addItem(_id, _num - 1);
    }
}

void CBag::renderBagUI(CPosition renderPt)
{
    //���δ�ӡ����
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //�ȴ�ӡ�����߿�
            if ((i == 0 || i == row - 1) || (j == 0 || j == col - 1))
            {
                //��λҪ��ӡ�� �ط�
                CUtils::gotoXY(renderPt.getX() + i, (renderPt.getY() + j) * 2);

                CUtils::setColor(64);
                cout << "��";
                CUtils::setColor();
            }
            else
            {
                //���ӡ������Ԫ��
                if (m_logicBag.count(CPosition(i, j)) == 1)  //�жϼ�ֵ���Ƿ����
                {
                    auto pBagUnit = m_logicBag[CPosition(i, j)];
                    auto itemId = pBagUnit->getID();
                    auto go = CItemFactory::createItem(itemId);

                    //��ӡ��Ʒ
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
    //����������ֵ
    col = COLOFBAG;
    row = ROLOFBAG;

    //����������ֵ
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
        //�ռ��������Ҫ�鿴��Ʒ
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
            //ȷ�� ������Ʒ����
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
