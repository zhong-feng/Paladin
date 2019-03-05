#include "CDog.h"


CDog::CDog()
{
    monsterID = MI_DOG;

    //���ⲿ�ļ���������
    initMonsterPropOnXml(MI_DOG);

    //ȷ��������
    skillNameArray[0] = "˺ҧ";
    skillUseMPArray[0] = 200;
}

CDog::~CDog()
{

}

void CDog::skillAttack1(CBasePerson** _role)
{
    //����
    curMP -= 200;

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

    //��ʾ����������
    _role[0]->showAttacked();

    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack30.wav");
}

void CDog::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //ѡ�񹥻���ʽ
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
    default: break;
    }

    //��¼ս����Ϣ
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " �� " + _role[roleNum]->getName() + " ʹ������ͨ����";   break; }
    case 1: {message = message + " �� " + _role[roleNum]->getName() + " ʹ����˺ҧ";   break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CDog::printFace()
{
    //�����ӡ��ͬ����ɫ��
    CUtils::setColor(10);

    printBaseFace();

    //����ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

void CDog::renderMyself()
{
    cout << "��" << endl;
}
