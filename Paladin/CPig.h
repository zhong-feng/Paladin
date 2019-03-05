#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CPig : public CMonster
{
public:
    CPig();
    ~CPig();


    //��д Ұ�� �ļ���  ��ײ (_role)
    // 50% ѣ�� 3 �غϣ������ӳ� 1.5  ����MP 100
    void skillAttack1(CBasePerson** _role)override;

    //��д Ұ�� �ļ���  ��Ƥ (�Լ�)
    //�ظ�HP 200 ���������ü� 30  ����MP 150
    void skillAttack2(CBasePerson** _monster)override;

    //��д ս�� ���� 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //��д ��ӡ��״
    void printFace();

    virtual void renderMyself()override;

};

