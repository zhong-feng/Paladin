#pragma once
#include "CBagUnit.h"
class CBag
{
public:
    CBag();
    ~CBag();

    //��������Ⱦ���� -- ���� �������߼����� ����Ⱦ
    void renderBagUI(CPosition renderPt);

    //�����Ʒ  (ÿ�����һ��  �ݹ����)
    bool addItem(CItemID _id, int _num = 1);

    //�鿴��Ʒ������
    int getCountItemID(CItemID _id);

    //�Ͻ�������Ʒ
    bool giveItemToTask(CItemID _id,int _num );

    //ʹ����Ʒ
    CItemID useItem(CPosition pos, int _num = 1);

    //���ҵ�Ԫ��
    CBagUnit* getBagUnit(CPosition pos);

protected:
    //�ռ���Ʒ������
    void doTaskOfCollect(CItemID _id);

    //����������� ��ʾ��Ϣ
    void showFull();

    //�����ĳ�ʼ��
    void onInit();

    //������ ��Ʒid ��ͬ����û�����ĵ�Ԫ�� (���ص�����)
    map<CPosition, CBagUnit*>::iterator findUnitByItemID(CItemID _id);

    //�ҵ���һ���յĵ�Ԫ�� (���ص�����)
    map<CPosition, CBagUnit*>::iterator findFirstEmpty();

protected:
    map<CPosition, CBagUnit*> m_logicBag;   //�߼��ϵı���

    GS_SYNTHESIZE(int, row, Row);
    GS_SYNTHESIZE(int, col, Col);
};

