#pragma once
#include "CMonster.h"

#include "CRole.h"
//单例
class CYaHui : public CRole, public CSingleton<CYaHui>
{
public:
    CYaHui();

    ~CYaHui();


    //重写 战斗 方法  
    void fight(CBasePerson** _role, CBasePerson** _monster);

    //重写赵灵儿的技能  施毒术
    // 50% 中毒 3 回合，每回合掉血 50 消耗MP 150
    void skillAttack1(CBasePerson** _monster)override;

    //重写赵灵儿的技能  回天术
    //回复HP 700  消耗MP 200
    void skillAttack2(CBasePerson** _role)override;

    //重写赵灵儿的技能  群体治疗
    //回复HP 500  消耗MP 200
    void skillAttack3(CBasePerson** _role)override;


    //升级方法 重写
    virtual void levelUp() override;

    //虚函数 打印形状
    virtual void printFace() override;

    //根据属性 补全数据
    virtual void initDataForAttribute();
};

