#pragma once
//#include "CBasePerson.h"
#include "CMonster.h"
#include "bagData.h"

class CRole :public CBasePerson
{
public:
    CRole();
    ~CRole();

    //��ӡ��Ϣ
    void printInfo()override;

    //�麯�� ��ӡ��״
    virtual void printFace() = 0;

    //�������� ���麯��
    virtual void levelUp() = 0;

    //��ӡ��״
    void printBaseFace();

    //�������� ��ȫ����
    virtual void initDataForAttribute() = 0;

protected:
    //��ʼ��
    void initMonsterPropOnXml(CRoleID _ID);

    //ȷ����ӡ��׼��
    CPosition findBasePos();

    //����������ʾ
    void eraseSkill(int _choiceSkillNum);

    //��ӡ�����б�
    void renderSkill();

    //ѡ����
    int choiceSkill();

    //����˵��
    void describeSkill(int _choiceNum);

    //ָ���ܵļ�ͷ����
    void upFlagSkill(int& choiceNum, CPosition _bacePos);
    //ָ���ܵļ�ͷ����
    void downFlagSkill(int& choiceNum, CPosition _bacePos);

    //ѡ�� ���� Ŀ��
    CBasePerson** choicePerson(CBasePerson** _person, bool isMonster);

    //ѡ�� ���� Ŀ�� �������
    void upFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum);
    //ѡ�� ���� Ŀ�� �������
    void downFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum);

    //ѡ��ʹ����Ʒ
    void useingItem()
    {

    }

protected:
    string skillDescribe[MAXSKILLNUM];

    GS_SYNTHESIZE(int, level, Level);     //�ȼ�
    GS_SYNTHESIZE(int, curEXP, CurEXP);   //��ǰ����
    GS_SYNTHESIZE(int, maxEXP, MaxEXP);   //�����

    //����
    GS_SYNTHESIZE(int, strength, Strength);        //����
    GS_SYNTHESIZE(int, agility, Agility);          //����
    GS_SYNTHESIZE(int, intelligence, Intelligence);//����

    GS_SYNTHESIZE(int, basicAttack, BasicAttack);   //����������
    GS_SYNTHESIZE(int, basicDefence, BasicDefence); //����������

    GS_SYNTHESIZE(CRoleInScene, posOfScene, PosOfScene);     //λ��

    GS_SYNTHESIZE(CItemID, weaponID, WeaponID);     //װ�� ����
    GS_SYNTHESIZE(CItemID, garmentID, GarmentID);     //    �·�
};

