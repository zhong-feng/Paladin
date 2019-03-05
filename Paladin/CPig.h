#pragma once
#include "CMonster.h"
#include "CFightDirector.h"

class CPig : public CMonster
{
public:
    CPig();
    ~CPig();


    //重写 野猪 的技能  冲撞 (_role)
    // 50% 眩晕 3 回合，攻击加成 1.5  消耗MP 100
    void skillAttack1(CBasePerson** _role)override;

    //重写 野猪 的技能  厚皮 (自己)
    //回复HP 200 防御力永久加 30  消耗MP 150
    void skillAttack2(CBasePerson** _monster)override;

    //重写 战斗 方法 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //重写 打印形状
    void printFace();

    virtual void renderMyself()override;

};

