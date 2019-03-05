#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CDevil :
    public CMonster
{
public:
    CDevil();
    ~CDevil();

    //重写 技能  烈火术
    // 攻击加成1.2 消耗MP 100
    void skillAttack1(CBasePerson** _role)override;

    //重写 技能  陨石天降
    //50%  眩晕 3 回合 攻击加成1.5 消耗MP 100
    void skillAttack2(CBasePerson** _role)override;

    //重写 技能  地狱烈焰
    //攻击敌方所有人 攻击加成1.3  消耗MP 150
    void skillAttack3(CBasePerson** _role)override;

    //重写 战斗 方法 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //重写 打印形状
    void printFace();

};

