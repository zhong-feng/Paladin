#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CDevil :
    public CMonster
{
public:
    CDevil();
    ~CDevil();

    //��д ����  �һ���
    // �����ӳ�1.2 ����MP 100
    void skillAttack1(CBasePerson** _role)override;

    //��д ����  ��ʯ�콵
    //50%  ѣ�� 3 �غ� �����ӳ�1.5 ����MP 100
    void skillAttack2(CBasePerson** _role)override;

    //��д ����  ��������
    //�����з������� �����ӳ�1.3  ����MP 150
    void skillAttack3(CBasePerson** _role)override;

    //��д ս�� ���� 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //��д ��ӡ��״
    void printFace();

};

