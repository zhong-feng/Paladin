#pragma once
#include "CMonster.h"

#include "CRole.h"

//����
class CQiuDao :  public CRole, public CSingleton<CQiuDao>
{
public:
    CQiuDao();
    ~CQiuDao();

    //��д ս�� ���� 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //��д ����  �Ƽ���
    //30% �������ü��� 50 �����ӳ�1.2 ����MP 150
    void skillAttack1(CBasePerson** _monster)override;

    //��д ����  ǿ��һ��
    //50%  ѣ�� 3 �غ� �����ӳ�1.5 ����MP 200
    void skillAttack2(CBasePerson** _monster)override;

    //��д ����  �򽣾�
    //�����з������� �����ӳ�1.3  ����MP 200
    void skillAttack3(CBasePerson** _monster)override;


    //�������� ��д
    virtual void levelUp() override;

    //�麯�� ��ӡ��״
    virtual void printFace() override;

    //�������� ��ȫ����
    virtual void initDataForAttribute();
};

