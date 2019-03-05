#pragma once
#include "fightData.h"

#include "CFightScene.h"

class CBasePerson
{
public:
    CBasePerson();
    ~CBasePerson();

    //设计 战斗过程的 普通攻击 行为 ---- 函数
    virtual void normalAttack(CBasePerson** _person);

    virtual void skillAttack1(CBasePerson**) = 0;
    virtual void skillAttack2(CBasePerson**) = 0;
    virtual void skillAttack3(CBasePerson**) = 0;

    //战斗 方法  纯虚函数
    virtual void fight(CBasePerson** _role, CBasePerson** _monster) = 0;

    //渲染 当前的状态信息   
    virtual void printInfo() = 0;

    //渲染 对应的图形
    virtual void printFace()=0;
    virtual void printBaseFace() = 0;

    //显示被攻击的动画
    void showAttacked();

    //FightBuff持续时间 -1
    void subFightBuffTime();

    string getSkillNameArray(int index);

    int getSkillUseMPArray(int index);

    map<CFightBuff, int>* getMapBuff();

protected:
    string skillNameArray[MAXSKILLNUM];
    int skillUseMPArray[MAXSKILLNUM];

    GS_SYNTHESIZE(string, name, Name);      //名字

    map<CFightBuff, int> mapBuff;  //战斗状态 + 持续时间 

    GS_SYNTHESIZE(int, curHP, CurHP);   //当前血量 
    GS_SYNTHESIZE(int, maxHP, MaxHP);   //最大血量 

    GS_SYNTHESIZE(int, curMP, CurMP); //current Magic point
    GS_SYNTHESIZE(int, maxMP, MaxMP); //max Magic point

    GS_SYNTHESIZE(int, reaAttack, ReaAttack);   //实际 攻击力
    GS_SYNTHESIZE(int, reaDefence, ReaDefence); //实际 防御力

    GS_SYNTHESIZE(bool, isShow, IsShow); //标记是否显示


};

