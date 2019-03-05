#include "CYaHui.h"
#include "CFightDirector.h"

 CYaHui::CYaHui()
{
    level = 1;
    maxEXP = level * 100;

    posOfScene = RS_TWO;

    skillNameArray[0] = "ʩ����";
    skillNameArray[1] = "������";
    skillNameArray[2] = "Ⱥ������";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 200;

    skillDescribe[0] = "ʩ������#���1.2����������50%�ĸ���ʹ�����ж���#����MP150.";
    skillDescribe[1] = "��������#�ָ�Ŀ��700HP��#����MP200.";
    skillDescribe[2] = "Ⱥ�����ƣ�#�ҷ�ȫ��ظ�500HP��#����MP200.";

    isShow = false;

    //���ļ���������
    initMonsterPropOnXml(RI_YAHUI);

    //ȷ�Ϲ��� Ѫ��
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;
}

 CYaHui::~CYaHui()
{

}

//��д ս�� ����  

 void CYaHui::fight(CBasePerson ** _role, CBasePerson ** _monster)
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
    case 2: {skillAttack2(choicePerson(_role, false)); break; }
    case 3: {skillAttack3(_role); break; }
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
    case 1: {message = message + " ʹ����ʩ����"; break; }
    case 2: {message = message + " ʹ���˻�����"; break; }
    case 3: {message = message + " ʹ����Ⱥ������"; break; }
    case 4: {message = message + " ʹ����ҩ��"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

//��д������ļ���  ʩ����
// 50% �ж� 3 �غϣ�ÿ�غϵ�Ѫ 50 ����MP 150

 void CYaHui::skillAttack1(CBasePerson ** _monster)
{

    //����
    curMP -= skillUseMPArray[0];

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
        _monster[0]->getMapBuff()->insert(make_pair(FB_ZHONGDU, 3));
    }

    //��ʾ����������
    _monster[0]->showAttacked();

    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack10.wma");

    
}

//��д������ļ���  ������
//�ظ�HP 700  ����MP 200

 void CYaHui::skillAttack2(CBasePerson ** _role)
{
    //����
    curMP -= skillUseMPArray[1];

    //��Ѫ
    _role[0]->setCurHP(_role[0]->getCurHP() + 700);
    if (_role[0]->getCurHP() > _role[0]->getMaxHP())
    {
        _role[0]->setCurHP(_role[0]->getMaxHP());
    }

    //��ʾ����
    _role[0]->showAttacked();


    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack11.wma");
}

//��д������ļ���  Ⱥ������
//�ظ�HP 500  ����MP 200

 void CYaHui::skillAttack3(CBasePerson ** _role)
{
    //����
    curMP -= skillUseMPArray[2];

    //�����������˻�Ѫ
    for (int i = 0; i < 2; i++)
    {
        if (_role[i]->getIsShow() == true)
        {
            //��Ѫ
            _role[i]->setCurHP(_role[i]->getCurHP() + 500);
            if (_role[i]->getCurHP() > _role[i]->getMaxHP())
            {
                _role[i]->setCurHP(_role[i]->getMaxHP());
            }

            //��ʾ����
            _role[i]->showAttacked();

            //��Ч
            CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack11.wma");
        }

    }
}

//�������� ��д

 void CYaHui::levelUp()
{
    if (curEXP < maxEXP)
    {
        return;
    }

    //����
    level++;
    curEXP -= maxEXP;
    maxEXP = level * 100;

    strength += 4;
    agility += 6;
    intelligence += 10;

    //���¹�������
    initDataForAttribute();

    curHP = maxHP;
    curMP = maxMP;


    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\levelUp.wav");

    return levelUp();
}

//�麯�� ��ӡ��״

 void CYaHui::printFace()
{
    //��ӡ��ͬ����ɫ��
    CUtils::setColor(42);

    printBaseFace();

    //����ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

//�������� ��ȫ����

 void CYaHui::initDataForAttribute()
{
     maxHP = strength * 100;
     maxMP = intelligence * 100;

    reaAttack = basicAttack + intelligence * 10;
    reaDefence = basicDefence + agility * 10;
}
