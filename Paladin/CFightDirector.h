#pragma once
#include "CSceneFactory.h"
#include "CMonsterFactory.h"
#include "CQiuDao.h"
#include "CYaHui.h"


class CFightDirector :public CSingleton<CFightDirector>
{
public:
    CFightDirector();
    ~CFightDirector();

    //ս���߼�
    int startFight(CMonsterID monsterType);

    vector<string>* getFightVec();
protected:
    //ʤ���� ��ɱ������
    void doTaskOfKillMonster();

    //��ӡս����Ϣ
    void printStateInfo(CPosition _statePos);

    //�ж�ʤ��
    int isWin();

    //���ﶼ������
    bool isRoleAllDead();

    //���ﶼ������
    bool isMonsterAllDead();

    //������ɫ��Ϣ
    void createRole();

    //����������Ϣ
    void createMonster(CMonsterID _monsterType);

    //���� pig ����������Ϣ
    void creatPig();

    //���� dog ����������Ϣ
    void creatDog();

    //���� Devil ����������Ϣ
    void creatDevil();

    ////�ͷ� ��ɫ ����
    //void freeRoleDate()
    //{
    //    if (role == 0)
    //    {
    //        return;
    //    }

    //    //�ͷŽ�ɫ����
    //    for (int i = 0; i < 2; i++)
    //    {
    //        if (role[i])
    //        {
    //            delete role[i];
    //            role[i] = 0;
    //        }
    //    }

    //    delete[] role;
    //    role = 0;
    //}

    //�ͷ� ���� ����
    void freeMonsterData();

protected:
    vector<string> fightVec;

    CBasePerson** role;
    CBasePerson** monster;

};

