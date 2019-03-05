#pragma once
#include "CBag.h"

#include "CSelectedCursor.h"

class CBagDirector :public CSingleton<CBagDirector>
{
public:
    CBagDirector();
    ~CBagDirector();


    //���뱳��ϵͳ
    int enterBagSystem();

    //��ӡ������Ϣ
    void renderBag();

    int getMoney();
    void setMoney(int _num);

    CBag* getBag();

protected:
    //ѡ�������굥Ԫ��
    void enterSelectedCurosor();

    //������Ʒ
    void castOffItem();

    //������Ʒ
    void saleItem();
    

    //��ѡ�б����ؿ�ѡ���ֵ��
    int renderCanChoiceList();

    //ʹ�ù��ѡ�����Ʒ
    void useTheSelectedCursorItem();

    //װ�� ����
    void useWeapon(CItem* _weapon,CRole* _role);

    //װ�� ����
    void useGarment(CItem* _garment, CRole* _role);
    
    //��ʾ��Ϣ ������Ⱦ
    void renderMessageUIScence();

    //���� ��ʾ��Ϣ ������Ⱦ
    void eraserMessageUIScence();

    //��Ⱦ ѡ�� ������
    int renderChoiceUIScene();

    //����ѡ����
    void eraserChoiceUIScene();

    //��������Ʒ 1-3��
    void randomAddItem();

    //�ƶ����
    void moveSelectedCursor(CDirection _direction);

    //����ϵͳ�ĳ�ʼ��
    void onInit();

    //�����ɵ���Ʒ��ʾ��Ϣ
    void eraserItemInfo();

    //��ӡ������Ϣ
    void renderHelpInfo();

    //��ӡ��Ʒ��ʾ��Ϣ
    void displaySelectedItemInfo();

    //����ϵͳ����Ⱦ����--------------
    void renderBagSystemUI();

protected:
    //�������� ����������߼� + ������ͼ��
    CBag * m_pBag;

    //��ӡ������������
    CPosition pointOfBagStartRender;

    //��ӡ��Ʒ��Ϣ�����
    CPosition pointOfShowItemInfo;

    //��ӡ��ʾ��Ϣ�����
    CPosition pointOfShowHelpInfo;

    //��ѡ���꡿
    CSelectedCursor selectedCursor;

    //��Ǯ
    static int money;
};

