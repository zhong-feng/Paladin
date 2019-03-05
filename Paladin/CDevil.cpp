#include "CDevil.h"


CDevil::CDevil()
{
    monsterID = MI_Devil;

    //从外部文件配置属性
    initMonsterPropOnXml(MI_Devil);

    //确定技能名
    skillNameArray[0] = "烈火术";
    skillNameArray[1] = "陨石天降";
    skillNameArray[2] = "地狱烈焰";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 250;
}

CDevil::~CDevil()
{

}

void CDevil::skillAttack1(CBasePerson** _role)
{
    //扣蓝
    curMP -= 100;

    //计算伤害
    int damage = reaAttack * 120 / 100 - _role[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //扣血
    _role[0]->setCurHP(_role[0]->getCurHP() - damage);
    if (_role[0]->getCurHP() < 0)
    {
        _role[0]->setCurHP(0);
    }

    //显示被攻击动画
    _role[0]->showAttacked();


    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
}

void CDevil::skillAttack2(CBasePerson** _role)
{
    //扣蓝
    curMP -= 100;

    //计算伤害
    int damage = reaAttack * 150 / 100 - _role[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //扣血
    _role[0]->setCurHP(_role[0]->getCurHP() - damage);
    if (_role[0]->getCurHP() < 0)
    {
        _role[0]->setCurHP(0);
    }

    //中状态
    if ((rand() + rand()*rand()) % 100 > 50)
    {
        _role[0]->getMapBuff()->insert(make_pair(FB_XUANYUN, 3));
    }

    //显示被攻击动画
    _role[0]->showAttacked();

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
}

void CDevil::skillAttack3(CBasePerson** _role)
{
    //扣蓝
    curMP -= 150;

    //给所有 role 造成伤害
    for (int i = 0; i < 2; i++)
    {
        if (_role[i]->getIsShow() == true)
        {
            //计算伤害
            int damage = reaAttack * 150 / 100 - _role[i]->getReaDefence();
            if (damage <= 0)
            {
                damage = 1;
            }

            //扣血
            _role[i]->setCurHP(_role[i]->getCurHP() - damage);
            if (_role[i]->getCurHP() < 0)
            {
                _role[i]->setCurHP(0);
            }

            //显示被攻击动画
            _role[i]->showAttacked();

            //音效
            CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
        }

    }
}

void CDevil::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //选择攻击方式
    int skillNum = 0;

    while (true)
    {
        skillNum = (rand() + rand()*rand()) % 4;

        if (skillNum == 0)
        {
            break;
        }

        if (skillUseMPArray[skillNum - 1] > curMP)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    //选择攻击对象
    int roleNum = 0;

    while (true)
    {
        roleNum = (rand() + rand()*rand()) % 2;

        if (_role[roleNum]->getIsShow() == false || _role[roleNum]->getCurHP() <= 0)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    //确定攻击行为
    switch (skillNum)
    {
    case 0: {normalAttack(_role + roleNum);   break; }
    case 1: {skillAttack1(_role + roleNum);   break; }
    case 2: {skillAttack2(_role + roleNum);   break; }
    case 3: {skillAttack3(_role);   break; }
    default: break;
    }

    //记录战斗信息
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了普通攻击";   break; }
    case 1: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了烈火术";   break; }
    case 2: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了陨石天降";   break; }
    case 3: {message = message + " 使用地狱烈焰";   break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CDevil::printFace()
{
    //怪物打印不同的颜色、
    CUtils::setColor(12);

    printBaseFace();

    //将颜色改回默认值
    CUtils::setColor();
}
