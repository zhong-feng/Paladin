#pragma once
#include "CBasePerson.h"

class CMonster :public CBasePerson
{
public:
    CMonster();
    virtual ~CMonster();

    //怪物巡逻
    void moveMyself(int** ppArrayScene);

    //重载 空的技能
    virtual void skillAttack1(CBasePerson**) override;
    virtual void skillAttack2(CBasePerson**) override;
    virtual void skillAttack3(CBasePerson**) override;

    //打印信息
    void printInfo()override;

    void printBaseFace();

    virtual void renderMyself();

protected:
    //初始化
    void initMonsterPropOnXml( CMonsterID _ID);

    //确定打印基准点
    CPosition findBasePos();


public:
    //计数 
    static int countNum;
    GS_SYNTHESIZE(int, orderNum, OrderNum); // 序号

protected:
    GS_SYNTHESIZE(CMonsterID, monsterID, MonsterID); //

    GS_SYNTHESIZE(CPosition, prePos, PrePos); //初始位置
    GS_SYNTHESIZE(CPosition, curPos, CurPos); //当前位置

    GS_SYNTHESIZE(int, territory, Territory); //巡逻范围
    GS_SYNTHESIZE(int, moveSpeed, MoveSpeed); //巡逻速度
    GS_SYNTHESIZE(DWORD, dwPreTime, DwPreTime); //创建的时间



};
