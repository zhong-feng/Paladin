#include "CPig.h"

CPig::CPig()
{
    monsterID = MI_PIG;

    //从外部文件配置属性
    initMonsterPropOnXml(MI_PIG);

    //确定技能名
    skillNameArray[0] = "冲撞";
    skillNameArray[1] = "厚皮";

    skillUseMPArray[0] = 200;
    skillUseMPArray[1] = 150;
}



void CPig::skillAttack1(CBasePerson** _role)
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
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CPig::skillAttack2(CBasePerson** _monster)
{
    //扣蓝
    curMP -= 150;

    //加血
    curHP += 200;
    if (curHP > maxHP)
    {
        curHP = maxHP;
    }

    //加防御
    reaDefence += 30;

    //显示动画
    showAttacked();


    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CPig::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //选择攻击方式
    int skillNum = 0;

    while (true)
    {
        skillNum = (rand() + rand()*rand()) % 3;

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
    case 2: {skillAttack2(0);   break; }
    default: break;
    }

    //记录战斗信息
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了普通攻击";   break; }
    case 1: {message = message + " 对 " + _role[roleNum]->getName() + " 使用了冲撞";   break; }
    case 2: {message = message + " 对 自己使用了厚皮"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CPig::printFace()
{
    //怪物打印不同的颜色、
    CUtils::setColor(14);

    printBaseFace();

    //将颜色改回默认值
    CUtils::setColor();
}

CPig::~CPig()
{

}

void CPig::renderMyself()
{
    cout << "猪" << endl;
}
