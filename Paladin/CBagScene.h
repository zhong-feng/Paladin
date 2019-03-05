#pragma once
#include "CScene.h"
#include "CBagDirector.h"

class CBagScene : public CScene
{
public:
    CBagScene();
    ~CBagScene();

    //��Ҫ����װ��Һͳ�������Ϸ��������
    virtual int enterUIScene();

protected:
    //���񲿷�------------------------------------------

    //ѡ������.
    int choiceTask();

    //��ӡ��ɫ��������
    void renderRedTask();

    //��ӡ���񱳾��߿�
    void renderTaskBackground();

    //��ӡ������Ϣ
    void renderTaskInfo();


    //���Բ���------------------------------------------

    //ѡ������
    int choiceAttribute();

    //��ӡ��ɫ ���� ����
    void renderRedAttribute();

    //��ӡ���ɵ�����
    void renderQiuXian();

    //��ӡ�Żݵ�����
    void renderYaHui();

    //��ÿ������
    void levelUpAll();


    //�̵겿��------------------------------------------

    //��ӡѡ���̵�
    int choiceShop();

    //�����̵�
    int enterShop();

    //��ӡ�ֽ���
    void renderLine();

    //��ӡ��ɫ �̵� ����
    void renderRedShop();

    void buyItem(CPosition _choice);

    //��ӡѡ����
    void renderSelected(CPosition _pos);

    //������Ʒ��ʾ��Ϣ
    void eraserItemInfo();

    //��ӡ�̵� ��1.HP 2.MP 3.���� 4.���� ��
    void renderShopStyle();


    //��������-----------------------------------

    //��ӡ�߿�
    void renderBorder();

    //��ӡ������Ϣ
    void renderHelpInfo();

    //���ി�鷽��--------------------------------

    //������ӡ����
    virtual void renderSceneUI();
    //�ӳ��������ȡ����
    virtual void initPropsOnSceneArray();

};

