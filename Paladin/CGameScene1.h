#pragma once

#include "CMonster.h"

class CGameScene1 : public CScene
{
public:
    CGameScene1();
    ~CGameScene1();

    //重要：封装玩家和场景的游戏交互过程
    virtual int enterUIScene();

protected:
    //怪物巡逻
    void moveAllTheMonster();

    //与 怪物 碰撞
    void touchMonster();

    //与怪物战斗
    bool isWinOfFightWithMonster(CMonsterID _ID);

    //打印怪物
    void renderAllTheMonster();

    //场景打印函数
    virtual void renderSceneUI();

    //根据人物的坐标破除迷雾
    bool breakFog();

    //破除所有的迷雾
    void breakAllFog();

    //从场景数组读取配置
    virtual void initPropsOnSceneArray();



    void freeMonsterList();

public:
    //标志 是否被杀死 野鬼
    static bool devilIsDead;

protected:
    list<CMonster*> m_MonsterList;

    GS_SYNTHESIZE(CPosition, toScene2Pos, ToScene2Pos);
    GS_SYNTHESIZE(CPosition, toScene3Pos, ToScene3Pos);
    GS_SYNTHESIZE(CPosition, toBirthPos, ToBirthPos);

    //野鬼固定怪
    GS_SYNTHESIZE(CPosition, devilPos, DevilPos);


    GS_SYNTHESIZE(int, canLook, CanLook);

    //创建二维数组，覆盖地图做出迷雾效果
    static int arrayFog[COLOFGAMESCENE1][ROWOFGAMESCENE1];

    //添加属性，让河水流动
    bool flagRiver;

};

