#include "CBasePerson.h"

CBasePerson::CBasePerson()
{
    name = "";

    curHP = maxHP = 0;
    curMP = maxMP = 0;
    reaAttack = 0;
    reaDefence = 0;

    for (int i = 0; i < MAXSKILLNUM; i++)
    {
        skillNameArray[i] = "";
        skillUseMPArray[i] = 0;
    }
}

void CBasePerson::normalAttack(CBasePerson** _person)
{
    //�����˺�
    int damage = reaAttack - _person[0]->getReaDefence();
    if (damage <= 0)
    {
        damage = 1;
    }

    //��Ѫ
    _person[0]->setCurHP(_person[0]->getCurHP() - damage);
    if (_person[0]->getCurHP() < 0)
    {
        _person[0]->setCurHP(0);
    }

    //��ʾ��������Ч��
    _person[0]->showAttacked();
}

std::string CBasePerson::getSkillNameArray(int index)
{
    return skillNameArray[index];
}

int CBasePerson::getSkillUseMPArray(int index)
{
    return skillUseMPArray[index];
}

map<CFightBuff, int>* CBasePerson::getMapBuff()
{
    return &mapBuff;
}

CBasePerson::~CBasePerson()
{

}

void CBasePerson::showAttacked()
{
    //������ ��װ��ִ�ӡ�Լ�
    CUtils::setColor(79);
    printInfo();

    Sleep(100);

    //�Ļ�Ĭ�� ��ɫ
    CUtils::setColor();
    printInfo();
}

void CBasePerson::subFightBuffTime()
{
    //ѭ��������ÿ��״̬����ʱ�� -1
    for (auto itr = mapBuff.begin(); itr != mapBuff.end(); itr++)
    {
        itr->second = itr->second - 1;
    }


    //ɾ������ʱ��Ϊ0 ��״̬
    auto itr = mapBuff.begin();
    while (itr != mapBuff.end())
    {
        if (itr->second <= 0)
        {
            //ɾ������ʱ�� =0��״̬
            mapBuff.erase(itr);

            //������ʧЧ�����¸�ֵ
            itr = mapBuff.begin();

            continue;
        }

        itr++;
    }
}
