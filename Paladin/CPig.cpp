#include "CPig.h"

CPig::CPig()
{
    monsterID = MI_PIG;

    //���ⲿ�ļ���������
    initMonsterPropOnXml(MI_PIG);

    //ȷ��������
    skillNameArray[0] = "��ײ";
    skillNameArray[1] = "��Ƥ";

    skillUseMPArray[0] = 200;
    skillUseMPArray[1] = 150;
}



void CPig::skillAttack1(CBasePerson** _role)
{
    //����
    curMP -= 100;

    //�����˺�
    int damage = reaAttack * 150 / 100 - _role[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //��Ѫ
    _role[0]->setCurHP(_role[0]->getCurHP() - damage);
    if (_role[0]->getCurHP() < 0)
    {
        _role[0]->setCurHP(0);
    }

    //��״̬
    if ((rand() + rand()*rand()) % 100 > 50)
    {
        _role[0]->getMapBuff()->insert(make_pair(FB_XUANYUN, 3));
    }

    //��ʾ����������
    _role[0]->showAttacked();


    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CPig::skillAttack2(CBasePerson** _monster)
{
    //����
    curMP -= 150;

    //��Ѫ
    curHP += 200;
    if (curHP > maxHP)
    {
        curHP = maxHP;
    }

    //�ӷ���
    reaDefence += 30;

    //��ʾ����
    showAttacked();


    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CPig::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //ѡ�񹥻���ʽ
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

    //ѡ�񹥻�����
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

    //ȷ��������Ϊ
    switch (skillNum)
    {
    case 0: {normalAttack(_role + roleNum);   break; }
    case 1: {skillAttack1(_role + roleNum);   break; }
    case 2: {skillAttack2(0);   break; }
    default: break;
    }

    //��¼ս����Ϣ
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " �� " + _role[roleNum]->getName() + " ʹ������ͨ����";   break; }
    case 1: {message = message + " �� " + _role[roleNum]->getName() + " ʹ���˳�ײ";   break; }
    case 2: {message = message + " �� �Լ�ʹ���˺�Ƥ"; break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CPig::printFace()
{
    //�����ӡ��ͬ����ɫ��
    CUtils::setColor(14);

    printBaseFace();

    //����ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

CPig::~CPig()
{

}

void CPig::renderMyself()
{
    cout << "��" << endl;
}
