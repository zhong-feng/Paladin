#pragma once

#include "CMonster.h"

class CGameScene3 :public CScene
{
public:
    CGameScene3();
    ~CGameScene3();


    //重要：封装玩家和场景的游戏交互过程
    virtual int enterUIScene();


protected:
    //和怪物战斗
    bool isWinOfFightWithMonster(CMonsterID _ID);

    //从场景数组读取配置
    virtual void initPropsOnSceneArray();

    //场景打印函数
    virtual void renderSceneUI();



protected:
    GS_SYNTHESIZE(CPosition, toScene2Pos, ToScene2Pos);
    GS_SYNTHESIZE(CPosition, toScene1Pos, ToScene1Pos);

    GS_SYNTHESIZE(int, canLook, CanLook);

    GS_SYNTHESIZE(int, safetyArea, SafetyArea);
};

