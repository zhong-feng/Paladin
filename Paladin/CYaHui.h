#pragma once
#include "CMonster.h"

#include "CRole.h"
//����
class CYaHui : public CRole, public CSingleton<CYaHui>
{
public:
    CYaHui();

    ~CYaHui();


    //��д ս�� ����  
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //��д������ļ���  ʩ����
    // 50% �ж� 3 �غϣ�ÿ�غϵ�Ѫ 50 ����MP 150
    void skillAttack1(CBasePerson** _monster)override;

    //��д������ļ���  ������
    //�ظ�HP 700  ����MP 200
    void skillAttack2(CBasePerson** _role)override;

    //��д������ļ���  Ⱥ������
    //�ظ�HP 500  ����MP 200
    void skillAttack3(CBasePerson** _role)override;


    //�������� ��д
    virtual void levelUp() override;

    //�麯�� ��ӡ��״
    virtual void printFace() override;

    //�������� ��ȫ����
    virtual void initDataForAttribute();
};

