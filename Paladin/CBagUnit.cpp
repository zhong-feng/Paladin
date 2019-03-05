#include "CBagUnit.h"


int CBagUnit::getCapacaty()
{
    //���ж��Ƿ�Ϊ��
    if (isEmpty())
    {
        //Ĭ�ϴ����޸� ��999��
        return 999;
    }

    //����Ʒʱ  ȷ���ɵ�������
    int maxCount = 0;

    CItem* pTmpItem = CItemFactory::createItem(id);
    if (pTmpItem)
    {
        //ȷ���ɵ�������
        maxCount = pTmpItem->count;

        //�ֶ��ͷ�����
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
