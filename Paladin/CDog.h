#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CDog :
    public CMonster
{
public:
    CDog();
    ~CDog();

    //重写 野狗 的技能  撕咬
    //攻击加成 1.5 消耗MP 100
    void skillAttack1(CBasePerson** _role)override;

    //重写 战斗 方法 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //重写 打印形状
    void printFace();


    virtual void renderMyself()override;
};

