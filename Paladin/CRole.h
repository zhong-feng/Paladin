#pragma once
//#include "CBasePerson.h"
#include "CMonster.h"
#include "bagData.h"

class CRole :public CBasePerson
{
public:
    CRole();
    ~CRole();

    //打印信息
    void printInfo()override;

    //虚函数 打印形状
    virtual void printFace() = 0;

    //升级方法 纯虚函数
    virtual void levelUp() = 0;

    //打印形状
    void printBaseFace();

    //根据属性 补全数据
    virtual void initDataForAttribute() = 0;

protected:
    //初始化
    void initMonsterPropOnXml(CRoleID _ID);

    //确定打印基准点
    CPosition findBasePos();

    //擦除技能显示
    void eraseSkill(int _choiceSkillNum);

    //打印技能列表
    void renderSkill();

    //选择技能
    int choiceSkill();

    //技能说明
    void describeSkill(int _choiceNum);

    //指向技能的箭头上移
    void upFlagSkill(int& choiceNum, CPosition _bacePos);
    //指向技能的箭头下移
    void downFlagSkill(int& choiceNum, CPosition _bacePos);

    //选择 怪物 目标
    CBasePerson** choicePerson(CBasePerson** _person, bool isMonster);

    //选择 技能 目标 光标上移
    void upFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum);
    //选择 技能 目标 光标下移
    void downFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum);

    //选择使用物品
    void useingItem()
    {

    }

protected:
    string skillDescribe[MAXSKILLNUM];

    GS_SYNTHESIZE(int, level, Level);     //等级
    GS_SYNTHESIZE(int, curEXP, CurEXP);   //当前经验
    GS_SYNTHESIZE(int, maxEXP, MaxEXP);   //最大经验

    //属性
    GS_SYNTHESIZE(int, strength, Strength);        //力量
    GS_SYNTHESIZE(int, agility, Agility);          //敏捷
    GS_SYNTHESIZE(int, intelligence, Intelligence);//智力

    GS_SYNTHESIZE(int, basicAttack, BasicAttack);   //基础攻击力
    GS_SYNTHESIZE(int, basicDefence, BasicDefence); //基础防御力

    GS_SYNTHESIZE(CRoleInScene, posOfScene, PosOfScene);     //位置

    GS_SYNTHESIZE(CItemID, weaponID, WeaponID);     //装备 武器
    GS_SYNTHESIZE(CItemID, garmentID, GarmentID);     //    衣服
};

