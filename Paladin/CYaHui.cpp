#include "CYaHui.h"
#include "CFightDirector.h"

 CYaHui::CYaHui()
{
    level = 1;
    maxEXP = level * 100;

    posOfScene = RS_TWO;

    skillNameArray[0] = "施毒术";
    skillNameArray[1] = "回天术";
    skillNameArray[2] = "群体治疗";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 200;

    skillDescribe[0] = "施毒术：#造成1.2倍攻击，有50%的概率使敌人中毒，#消耗MP150.";
    skillDescribe[1] = "回天术：#恢复目标700HP，#消耗MP200.";
    skillDescribe[2] = "群体治疗：#我方全体回复500HP，#消耗MP200.";

    isShow = false;

    //从文件配置属性
    initMonsterPropOnXml(RI_YAHUI);

    //确认攻防 血蓝
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;
}

 CYaHui::~CYaHui()
{

}

//重写 战斗 方法  

 void CYaHui::fight(CBasePerson ** _role, CBasePerson ** _monster)
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
    case 2: {skillAttack2(choicePerson(_role, false)); break; }
    case 3: {skillAttack3(_role); break; }
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
    case 1: {message = message + " 使用了施毒术"; break; }
    case 2: {message = message + " 使用了回天术"; break; }
    case 3: {message = message + " 使用了群体治疗"; break; }
    case 4: {message = message + " 使用了药物"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

//重写赵灵儿的技能  施毒术
// 50% 中毒 3 回合，每回合掉血 50 消耗MP 150

 void CYaHui::skillAttack1(CBasePerson ** _monster)
{

    //扣蓝
    curMP -= skillUseMPArray[0];

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
        _monster[0]->getMapBuff()->insert(make_pair(FB_ZHONGDU, 3));
    }

    //显示被攻击动画
    _monster[0]->showAttacked();

    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack10.wma");

    
}

//重写赵灵儿的技能  回天术
//回复HP 700  消耗MP 200

 void CYaHui::skillAttack2(CBasePerson ** _role)
{
    //扣蓝
    curMP -= skillUseMPArray[1];

    //加血
    _role[0]->setCurHP(_role[0]->getCurHP() + 700);
    if (_role[0]->getCurHP() > _role[0]->getMaxHP())
    {
        _role[0]->setCurHP(_role[0]->getMaxHP());
    }

    //显示动画
    _role[0]->showAttacked();


    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack11.wma");
}

//重写赵灵儿的技能  群体治疗
//回复HP 500  消耗MP 200

 void CYaHui::skillAttack3(CBasePerson ** _role)
{
    //扣蓝
    curMP -= skillUseMPArray[2];

    //给己方所有人回血
    for (int i = 0; i < 2; i++)
    {
        if (_role[i]->getIsShow() == true)
        {
            //加血
            _role[i]->setCurHP(_role[i]->getCurHP() + 500);
            if (_role[i]->getCurHP() > _role[i]->getMaxHP())
            {
                _role[i]->setCurHP(_role[i]->getMaxHP());
            }

            //显示动画
            _role[i]->showAttacked();

            //音效
            CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack11.wma");
        }

    }
}

//升级方法 重写

 void CYaHui::levelUp()
{
    if (curEXP < maxEXP)
    {
        return;
    }

    //升级
    level++;
    curEXP -= maxEXP;
    maxEXP = level * 100;

    strength += 4;
    agility += 6;
    intelligence += 10;

    //更新攻防数据
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;


    //音效
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\levelUp.wav");

    return levelUp();
}

//虚函数 打印形状

 void CYaHui::printFace()
{
    //打印不同的颜色、
    CUtils::setColor(42);

    printBaseFace();

    //将颜色改回默认值
    CUtils::setColor();
}

//根据属性 补全数据

 void CYaHui::initDataForAttribute()
{
     maxHP = strength * 100;
     maxMP = intelligence * 100;

    reaAttack = basicAttack + intelligence * 10;
    reaDefence = basicDefence + agility * 10;
}
