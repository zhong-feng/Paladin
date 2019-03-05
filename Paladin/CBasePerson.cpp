#include "CBasePerson.h"

CBasePerson::CBasePerson()
{
    name = "";

    curHP = maxHP = 0;
    curMP = maxMP = 0;
    reaAttack = 0;
    reaDefence = 0;

    for (int i = 0; i < MAXSKILLNUM; i++)
    {
        skillNameArray[i] = "";
        skillUseMPArray[i] = 0;
    }
}

void CBasePerson::normalAttack(CBasePerson** _person)
{
    //计算伤害
    int damage = reaAttack - _person[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //扣血
    _person[0]->setCurHP(_person[0]->getCurHP() - damage);
    if (_person[0]->getCurHP() < 0)
    {
        _person[0]->setCurHP(0);
    }

    //显示被攻击的效果
    _person[0]->showAttacked();
}

std::string CBasePerson::getSkillNameArray(int index)
{
    return skillNameArray[index];
}

int CBasePerson::getSkillUseMPArray(int index)
{
    return skillUseMPArray[index];
}

map<CFightBuff, int>* CBasePerson::getMapBuff()
{
    return &mapBuff;
}

CBasePerson::~CBasePerson()
{

}

void CBasePerson::showAttacked()
{
    //被攻击 红底白字打印自己
    CUtils::setColor(79);
    printInfo();

    Sleep(100);

    //改回默认 颜色
    CUtils::setColor();
    printInfo();
}

void CBasePerson::subFightBuffTime()
{
    //循环遍历，每种状态持续时间 -1
    for (auto itr = mapBuff.begin(); itr != mapBuff.end(); itr++)
    {
        itr->second = itr->second - 1;
    }


    //删除持续时间为0 的状态
    auto itr = mapBuff.begin();
    while (itr != mapBuff.end())
    {
        if (itr->second <= 0)
        {
            //删除持续时间 =0的状态
            mapBuff.erase(itr);

            //迭代器失效，重新赋值
            itr = mapBuff.begin();

            continue;
        }

        itr++;
    }
}
