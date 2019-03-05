#pragma once

#include "CMonster.h"

class CGameScene2 : public CScene
{
public:
    CGameScene2();
    ~CGameScene2();


    //��Ҫ����װ��Һͳ�������Ϸ��������
    virtual int enterUIScene();


protected:
    //�͹���ս��
    bool isWinOfFightWithMonster(CMonsterID _ID);

    //�ӳ��������ȡ����
    virtual void initPropsOnSceneArray();

    //������ӡ����
    virtual void renderSceneUI();



protected:
    GS_SYNTHESIZE(CPosition, toScene1Pos, ToScene1Pos);
    GS_SYNTHESIZE(CPosition, toScene3Pos, ToScene3Pos);

    GS_SYNTHESIZE(int, canLook, CanLook);

    GS_SYNTHESIZE(int, safetyArea, SafetyArea);
};

