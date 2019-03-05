#include "CDog.h"


CDog::CDog()
{
    monsterID = MI_DOG;

    //从外部文件配置属性
    initMonsterPropOnXml(MI_DOG);

    //确定技能名
    skillNameArray[0] = "撕咬";
    skillUseMPArray[0] = 200;
}

CDog::~CDog()
{

}

void CDog::skillAttack1(CBasePerson** _role)
{
    //扣蓝
    curMP -= 200;

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

    //显示被攻击动画
    _role[0]->showAttacked();

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CDog::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //选择攻击方式
    int skillNum = 0;

    while (true)
    {
        skillNum = (rand() + rand()*rand()) % 2;

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
    default: break;
    }

    //记录战斗信息
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了普通攻击";   break; }
    case 1: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了撕咬";   break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CDog::printFace()
{
    //怪物打印不同的颜色、
    CUtils::setColor(10);

    printBaseFace();

    //将颜色改回默认值
    CUtils::setColor();
}

void CDog::renderMyself()
{
    cout << "狗" << endl;
}
