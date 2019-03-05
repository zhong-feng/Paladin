#include "CQiuDao.h"
#include "CFightDirector.h"

CQiuDao::CQiuDao()
{
    level = 1;
    maxEXP = level * 100;

    posOfScene = RS_ONE;

    skillNameArray[0] = "�Ƽ���";
    skillNameArray[1] = "ǿ��һ��";
    skillNameArray[2] = "�򽣾�";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 200;

    skillDescribe[0] = "�Ƽ�����#���1.2����������30%�ĸ���ʹ�������ü���50������#����MP150.";
    skillDescribe[1] = "ǿ��һ����#���1.5����������50%�ĸ���ʹ������ѣ��#����MP200.";
    skillDescribe[2] = "�򽣾���#�����е������1.3��������#����MP200.";

    isShow = true;

    //���ļ���������
    initMonsterPropOnXml(RI_QIUDAO);

    //ȷ�Ϲ��� Ѫ��
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

    //����
    level++;
    curEXP -= maxEXP;
    maxEXP = level * 100;

    strength += 10;
    agility += 6;
    intelligence += 4;

    //���¹�������
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;


    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\levelUp.wav");

    return levelUp();
}

void CQiuDao::printFace()
{
    //��ӡ��ͬ����ɫ��
    CUtils::setColor(43);

    printBaseFace();

    //����ɫ�Ļ�Ĭ��ֵ
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
    //����
    curMP -= skillUseMPArray[0];

    //�����˺�
    int damage = reaAttack * 120 / 100 - _monster[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //��Ѫ
    _monster[0]->setCurHP(_monster[0]->getCurHP() - damage);
    if (_monster[0]->getCurHP() < 0)
    {
        _monster[0]->setCurHP(0);
    }

    //��״̬
    if ((rand() + rand()*rand()) % 100 < 30)
    {
        _monster[0]->setReaDefence(_monster[0]->getReaDefence() - 50);
    }

    //��ʾ����������
    _monster[0]->showAttacked();

    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack00.wav");


}

void CQiuDao::skillAttack2(CBasePerson** _monster)
{
    //����
    curMP -= skillUseMPArray[1];

    //�����˺�
    int damage = reaAttack * 150 / 100 - _monster[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //��Ѫ
    _monster[0]->setCurHP(_monster[0]->getCurHP() - damage);
    if (_monster[0]->getCurHP() < 0)
    {
        _monster[0]->setCurHP(0);
    }

    //��״̬
    if ((rand() + rand()*rand()) % 100 > 50)
    {
        _monster[0]->getMapBuff()->insert(make_pair(FB_XUANYUN, 3));
    }

    //��ʾ����������
    _monster[0]->showAttacked();

    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack00.wav");

}

void CQiuDao::skillAttack3(CBasePerson** _monster)
{
    //����
    curMP -= skillUseMPArray[2];

    //�������е���
    for (int i = 0; i < CMonster::countNum; i++)
    {
        //�����˺�
        int damage = reaAttack * 150 / 100 - _monster[i]->getReaDefence();
        if (damage <= 0)
        {
            damage = 1;
        }

        //��Ѫ
        _monster[i]->setCurHP(_monster[i]->getCurHP() - damage);
        if (_monster[i]->getCurHP() < 0)
        {
            _monster[i]->setCurHP(0);
        }

        //��ʾ����������
        _monster[i]->showAttacked();

        //��Ч
        CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack03.wav");
    }
}

void CQiuDao::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //��ӡ�����б�
    renderSkill();

    //ѡ����
    int choiceSkillNum = choiceSkill();

    //���ݼ���ѡ����Ӧ�Ķ��� ���� ����
    switch (choiceSkillNum)
    {
    case 0: {normalAttack(choicePerson(_monster, true)); break; }
    case 1: {skillAttack1(choicePerson(_monster, true)); break; }
    case 2: {skillAttack2(choicePerson(_monster, true)); break; }
    case 3: {skillAttack3(_monster); break; }
        //ʹ��ҩƷ
    case 4:
    {

        break;
    }
    default:break;
    }

    //����������ʾ
    eraseSkill(choiceSkillNum);

    //��¼ս����Ϣ
    string message = this->name;

    switch (choiceSkillNum)
    {
    case 0: {message = message + " ʹ������ͨ����"; break; }
    case 1: {message = message + " ʹ�����Ƽ���" ;break; }
    case 2: {message = message + " ʹ����ǿ��һ��"; break; }
    case 3: {message = message + " ʹ�����򽣾�"; break; }
    case 4: {message = message + " ʹ����ҩ��"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}
