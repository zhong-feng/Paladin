#pragma once

#include "CMonster.h"

class CGameScene1 : public CScene
{
public:
    CGameScene1();
    ~CGameScene1();

    //��Ҫ����װ��Һͳ�������Ϸ��������
    virtual int enterUIScene();

protected:
    //����Ѳ��
    void moveAllTheMonster();

    //�� ���� ��ײ
    void touchMonster();

    //�����ս��
    bool isWinOfFightWithMonster(CMonsterID _ID);

    //��ӡ����
    void renderAllTheMonster();

    //������ӡ����
    virtual void renderSceneUI();

    //��������������Ƴ�����
    bool breakFog();

    //�Ƴ����е�����
    void breakAllFog();

    //�ӳ��������ȡ����
    virtual void initPropsOnSceneArray();



    void freeMonsterList();

public:
    //��־ �Ƿ�ɱ�� Ұ��
    static bool devilIsDead;

protected:
    list<CMonster*> m_MonsterList;

    GS_SYNTHESIZE(CPosition, toScene2Pos, ToScene2Pos);
    GS_SYNTHESIZE(CPosition, toScene3Pos, ToScene3Pos);
    GS_SYNTHESIZE(CPosition, toBirthPos, ToBirthPos);

    //Ұ��̶���
    GS_SYNTHESIZE(CPosition, devilPos, DevilPos);


    GS_SYNTHESIZE(int, canLook, CanLook);

    //������ά���飬���ǵ�ͼ��������Ч��
    static int arrayFog[COLOFGAMESCENE1][ROWOFGAMESCENE1];

    //������ԣ��ú�ˮ����
    bool flagRiver;

};

