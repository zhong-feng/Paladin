#pragma once
#include "CBasePerson.h"

class CMonster :public CBasePerson
{
public:
    CMonster();
    virtual ~CMonster();

    //����Ѳ��
    void moveMyself(int** ppArrayScene);

    //���� �յļ���
    virtual void skillAttack1(CBasePerson**) override;
    virtual void skillAttack2(CBasePerson**) override;
    virtual void skillAttack3(CBasePerson**) override;

    //��ӡ��Ϣ
    void printInfo()override;

    void printBaseFace();

    virtual void renderMyself();

protected:
    //��ʼ��
    void initMonsterPropOnXml( CMonsterID _ID);

    //ȷ����ӡ��׼��
    CPosition findBasePos();


public:
    //���� 
    static int countNum;
    GS_SYNTHESIZE(int, orderNum, OrderNum); // ���

protected:
    GS_SYNTHESIZE(CMonsterID, monsterID, MonsterID); //

    GS_SYNTHESIZE(CPosition, prePos, PrePos); //��ʼλ��
    GS_SYNTHESIZE(CPosition, curPos, CurPos); //��ǰλ��

    GS_SYNTHESIZE(int, territory, Territory); //Ѳ�߷�Χ
    GS_SYNTHESIZE(int, moveSpeed, MoveSpeed); //Ѳ���ٶ�
    GS_SYNTHESIZE(DWORD, dwPreTime, DwPreTime); //������ʱ��



};
