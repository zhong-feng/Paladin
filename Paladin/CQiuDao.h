#pragma once
#include "CMonster.h"

#include "CRole.h"

//单例
class CQiuDao :  public CRole, public CSingleton<CQiuDao>
{
public:
    CQiuDao();
    ~CQiuDao();

    //重写 战斗 方法 
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //重写 技能  破甲术
    //30% 防御永久减少 50 攻击加成1.2 消耗MP 150
    void skillAttack1(CBasePerson** _monster)override;

    //重写 技能  强力一击
    //50%  眩晕 3 回合 攻击加成1.5 消耗MP 200
    void skillAttack2(CBasePerson** _monster)override;

    //重写 技能  万剑诀
    //攻击敌方所有人 攻击加成1.3  消耗MP 200
    void skillAttack3(CBasePerson** _monster)override;


    //升级方法 重写
    virtual void levelUp() override;

    //虚函数 打印形状
    virtual void printFace() override;

    //根据属性 补全数据
    virtual void initDataForAttribute();
};

