#pragma once

#include "CMonster.h"

class CGameScene3 :public CScene
{
public:
    CGameScene3();
    ~CGameScene3();


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
    GS_SYNTHESIZE(CPosition, toScene2Pos, ToScene2Pos);
    GS_SYNTHESIZE(CPosition, toScene1Pos, ToScene1Pos);

    GS_SYNTHESIZE(int, canLook, CanLook);

    GS_SYNTHESIZE(int, safetyArea, SafetyArea);
};

