#include "CDevil.h"


CDevil::CDevil()
{
    monsterID = MI_Devil;

    //���ⲿ�ļ���������
    initMonsterPropOnXml(MI_Devil);

    //ȷ��������
    skillNameArray[0] = "�һ���";
    skillNameArray[1] = "��ʯ�콵";
    skillNameArray[2] = "��������";

    skillUseMPArray[0] = 150;
    skillUseMPArray[1] = 200;
    skillUseMPArray[2] = 250;
}

CDevil::~CDevil()
{

}

void CDevil::skillAttack1(CBasePerson** _role)
{
    //����
    curMP -= 100;

    //�����˺�
    int damage = reaAttack * 120 / 100 - _role[0]->getReaDefence();
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
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
}

void CDevil::skillAttack2(CBasePerson** _role)
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
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
}

void CDevil::skillAttack3(CBasePerson** _role)
{
    //����
    curMP -= 150;

    //������ role ����˺�
    for (int i = 0; i < 2; i++)
    {
        if (_role[i]->getIsShow() == true)
        {
            //�����˺�
            int damage = reaAttack * 150 / 100 - _role[i]->getReaDefence();
            if (damage <= 0)
            {
                damage = 1;
            }

            //��Ѫ
            _role[i]->setCurHP(_role[i]->getCurHP() - damage);
            if (_role[i]->getCurHP() < 0)
            {
                _role[i]->setCurHP(0);
            }

            //��ʾ����������
            _role[i]->showAttacked();

            //��Ч
            CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\attack20.wav");
        }

    }
}

void CDevil::fight(CBasePerson** _role, CBasePerson** _monster)
{
    //ѡ�񹥻���ʽ
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
    case 2: {skillAttack2(_role + roleNum);   break; }
    case 3: {skillAttack3(_role);   break; }
    default: break;
    }

    //��¼ս����Ϣ
    string message = this->name;

    switch (skillNum)
    {
    case 0: {message = message + " �� " + _role[roleNum]->getName() + " ʹ������ͨ����";   break; }
    case 1: {message = message + " �� " + _role[roleNum]->getName() + " ʹ�����һ���";   break; }
    case 2: {message = message + " �� " + _role[roleNum]->getName() + " ʹ������ʯ�콵";   break; }
    case 3: {message = message + " ʹ�õ�������";   break; }
    default: break;
    }

    auto tmpVec = CFightDirector::getInstance()->getFightVec();

    tmpVec->insert(tmpVec->begin(), message);
}

void CDevil::printFace()
{
    //�����ӡ��ͬ����ɫ��
    CUtils::setColor(12);

    printBaseFace();

    //����ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}
