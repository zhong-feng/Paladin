#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CDog :
    public CMonster
{
public:
    CDog();
    ~CDog();

    //��д Ұ�� �ļ���  ˺ҧ
    //�����ӳ� 1.5 ����MP 100
    void skillAttack1(CBasePerson** _role)override;

    //��д ս�� ���� 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //��д ��ӡ��״
    void printFace();


    virtual void renderMyself()override;
};

