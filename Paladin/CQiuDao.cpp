#include "CQiuDao.h"
#include "CFightDirector.h"

CQiuDao::CQiuDao()
{
    level = 1;
    maxEXP = level * 100;

    posOfScene = RS_ONE;

    skillNameArray[0] = "破甲术";
    skillNameArray[1] = "强力一击";
    skillNameArray[2] = "万剑诀";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 200;

    skillDescribe[0] = "破甲术：#造成1.2倍攻击，有30%的概率使敌人永久减少50防御，#消耗MP150.";
    skillDescribe[1] = "强力一击：#造成1.5倍攻击，有50%的概率使敌人晕眩，#消耗MP200.";
    skillDescribe[2] = "万剑诀：#对所有敌人造成1.3倍攻击，#消耗MP200.";

    isShow = true;

    //从文件配置属性
    initMonsterPropOnXml(RI_QIUDAO);

    //确认攻防 血蓝
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;
}

CQiuDao::~CQiuDao()
{

}

void CQiuDao::levelUp()
{
    if (curEXP < maxEXP)
    {
        return ;
    }

    //升级
    level++;
    curEXP -= maxEXP;
    maxEXP = level * 100;

    strength += 10;
    agility += 6;
    intelligence += 4;

    //更新攻防数据
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;


    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\levelUp.wav");

    return levelUp();
}

void CQiuDao::printFace()
{
    //打印不同的颜色、
    CUtils::setColor(43);

    printBaseFace();

    //将颜色改回默认值
    CUtils::setColor();
}

void CQiuDao::initDataForAttribute()
{
    maxHP = strength * 100;
    maxMP = intelligence * 100;

    reaAttack = basicAttack + strength * 10;
    reaDefence = basicDefence + agility * 10;
}

void CQiuDao::skillAttack1(CBasePerson** _monster)
{
    //扣蓝
    curMP -= skillUseMPArray[0];

    //计算伤害
    int damage = reaAttack * 120 / 100 - _monster[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //扣血
    _monster[0]->setCurHP(_monster[0]->getCurHP() - damage);
    if (_monster[0]->getCurHP() < 0)
    {
        _monster[0]->setCurHP(0);
    }

    //中状态
    if ((rand() + rand()*rand()) % 100 < 30)
    {
        _monster[0]->setReaDefence(_monster[0]->getReaDefence() - 50);
    }

    //显示被攻击动画
    _monster[0]->showAttacked();

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack00.wav");


}

void CQiuDao::skillAttack2(CBasePerson** _monster)
{
    //扣蓝
    curMP -= skillUseMPArray[1];

    //计算伤害
    int damage = reaAttack * 150 / 100 - _monster[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //扣血
    _monster[0]->setCurHP(_monster[0]->getCurHP() - damage);
    if (_monster[0]->getCurHP() < 0)
    {
        _monster[0]->setCurHP(0);
    }

    //中状态
    if ((rand() + rand()*rand()) % 100 > 50)
    {
        _monster[0]->getMapBuff()->insert(make_pair(FB_XUANYUN, 3));
    }

    //显示被攻击动画
    _monster[0]->showAttacked();

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack00.wav");

}

void CQiuDao::skillAttack3(CBasePerson** _monster)
{
    //扣蓝
    curMP -= skillUseMPArray[2];

    //攻击所有敌人
    for (int i = 0; i < CMonster::countNum; i++)
    {
        //计算伤害
        int damage = reaAttack * 150 / 100 - _monster[i]->getReaDefence();
        if (damage <= 0)
        {
            damage = 1;
        }

        //扣血
        _monster[i]->setCurHP(_monster[i]->getCurHP() - damage);
        if (_monster[i]->getCurHP() < 0)
        {
            _monster[i]->setCurHP(0);
        }

        //显示被攻击动画
        _monster[i]->showAttacked();

        //音效
        CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack03.wav");
    }
}

void CQiuDao::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //打印技能列表
    renderSkill();

    //选择技能
    int choiceSkillNum = choiceSkill();

    //根据技能选择相应的对象 发起 攻击
    switch (choiceSkillNum)
    {
    case 0: {normalAttack(choicePerson(_monster, true)); break; }
    case 1: {skillAttack1(choicePerson(_monster, true)); break; }
    case 2: {skillAttack2(choicePerson(_monster, true)); break; }
    case 3: {skillAttack3(_monster); break; }
        //使用药品
    case 4:
    {

        break;
    }
    default:break;
    }

    //擦除技能显示
    eraseSkill(choiceSkillNum);

    //记录战斗信息
    string message = this->name;

    switch (choiceSkillNum)
    {
    case 0: {message = message + " 使用了普通攻击"; break; }
    case 1: {message = message + " 使用了破甲术" ;break; }
    case 2: {message = message + " 使用了强力一击"; break; }
    case 3: {message = message + " 使用了万剑诀"; break; }
    case 4: {message = message + " 使用了药物"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}
