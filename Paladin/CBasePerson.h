#pragma once
#include "fightData.h"

#include "CFightScene.h"

class CBasePerson
{
public:
    CBasePerson();
    ~CBasePerson();

    //��� ս�����̵� ��ͨ���� ��Ϊ ---- ����
    virtual void normalAttack(CBasePerson** _person);

    virtual void skillAttack1(CBasePerson**) = 0;
    virtual void skillAttack2(CBasePerson**) = 0;
    virtual void skillAttack3(CBasePerson**) = 0;

    //ս�� ����  ���麯��
    virtual void fight(CBasePerson** _role, CBasePerson** _monster) = 0;

    //��Ⱦ ��ǰ��״̬��Ϣ   
    virtual void printInfo() = 0;

    //��Ⱦ ��Ӧ��ͼ��
    virtual void printFace()=0;
    virtual void printBaseFace() = 0;

    //��ʾ�������Ķ���
    void showAttacked();

    //FightBuff����ʱ�� -1
    void subFightBuffTime();

    string getSkillNameArray(int index);

    int getSkillUseMPArray(int index);

    map<CFightBuff, int>* getMapBuff();

protected:
    string skillNameArray[MAXSKILLNUM];
    int skillUseMPArray[MAXSKILLNUM];

    GS_SYNTHESIZE(string, name, Name);      //����

    map<CFightBuff, int> mapBuff;  //ս��״̬ + ����ʱ�� 

    GS_SYNTHESIZE(int, curHP, CurHP);   //��ǰѪ�� 
    GS_SYNTHESIZE(int, maxHP, MaxHP);   //���Ѫ�� 

    GS_SYNTHESIZE(int, curMP, CurMP); //current Magic point
    GS_SYNTHESIZE(int, maxMP, MaxMP); //max Magic point

    GS_SYNTHESIZE(int, reaAttack, ReaAttack);   //ʵ�� ������
    GS_SYNTHESIZE(int, reaDefence, ReaDefence); //ʵ�� ������

    GS_SYNTHESIZE(bool, isShow, IsShow); //����Ƿ���ʾ


};

