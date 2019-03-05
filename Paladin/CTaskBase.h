#pragma once
#include "taskData.h"

class CTaskBase
{
public:
    CTaskBase(CTaskID _id);
    ~CTaskBase();

    int enterTask(CSceneNPC speakNPC, CPosition _pos);

protected:
    //�ⲿ�ļ���������
    void initTaskPropOnXml(CTaskID _id);

    //��ӡ ������ѡ������
    void renderBackgroundOfChoice(CPosition _pos)
    {
        auto tmpPos = _pos;

        for (int i = 0; i < 4; i++)
        {
            CUtils::gotoXY(tmpPos);
            cout << "           ";
            tmpPos = tmpPos + DI_DOWN;
        }
        
        tmpPos = _pos + CPosition(1, 1);
        CUtils::gotoXY(tmpPos);
        cout << "�� ����";

        CUtils::gotoXY(tmpPos+DI_DOWN);
        cout << "   �ܾ�";
    }



    //����û����
    void enterTaskModde0(CSceneNPC speakNPC, CPosition _pos);

    //�������� ����û���
    void enterTaskModde1(CSceneNPC speakNPC, CPosition _pos);

    //������� ����û�ύ
    void enterTaskModde2(CSceneNPC speakNPC, CPosition _pos);

    //������������
    void giveReward();


    //��ӡ��ʾ��Ϣ
    void renderMessage(const char* str, CPosition _pos);

    //������Ϣ��ʾ��
    void eraserMessage(CPosition _pos);
public:
    CTaskID ID;          //���� ID
    CTaskType taskType;  //��������
    string name;         //��������

    CSceneNPC provideNpcID; //������ NPC ID
    CSceneNPC regainNpcID;  //������ NPC ID

    string info;      //����������Ϣ
    string receipt;   //ȷ�Ͻ���������Ϣ

    string accept;    //��������
    string refuse;    //�ܾ�����

    string unfiniseded;   //���� δ���
    string finished;      //���� �����

    CItemID itemID;    //������Ʒ ID
    int itemMax;       //��Ҫ�� ����
    int itemCount;     //���е� ����

    CMonsterID monsterID;     //������� ID
    int monsterMax;           //��Ҫ�� ����
    int monsterCount;         //���е� ����

    int giveMoney;     //�������
    CItemID giveItem;  //������Ʒ

    int taskMode;      //��ǰ����״̬

};

