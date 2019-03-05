#include "CMonster.h"

int CMonster::countNum=0;

CMonster::CMonster()
{
    isShow = true;

    monsterID = MI_NONE;

    moveSpeed = 0;
    dwPreTime = GetTickCount();  //��ȡ��ǰ����ʱ��

    orderNum = 0;
}

CMonster::~CMonster()
{

}


void CMonster::initMonsterPropOnXml(CMonsterID _ID)
{
    //�ļ�·��
    char* filePath = ".\\Resource\\Config\\Monster.xml";

    //����XML�ļ�����
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //�����ļ�
        //��ȡxml�ļ��ĸ�Ԫ�� (monsterSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //����ÿһ����Ԫ�� (monster)
        for (TiXmlElement* pMonsterElement = pSystemElement->FirstChildElement();
            pMonsterElement != nullptr;
            pMonsterElement = pMonsterElement->NextSiblingElement())
        {
            //���� ID �ҵ���Ӧ��  (monster)
            if ((CMonsterID)atoi(pMonsterElement->FirstAttribute()->Value()) == _ID)
            {
                //����ÿһ����Ԫ�� (��������)
                for (TiXmlElement* pAttributeElement = pMonsterElement->FirstChildElement();
                    pAttributeElement != nullptr;
                    pAttributeElement = pAttributeElement->NextSiblingElement())
                {
                    if (strcmp(pAttributeElement->Value() , "name")==0)
                    {
                        this->name = pAttributeElement->FirstChild()->ToText()->Value();
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value() , "HP")==0)
                    {
                        this->curHP = this->maxHP = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "MP") == 0)
                    {
                        this->curMP = this->maxMP = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value() , "attack") == 0)
                    {
                        this->reaAttack = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "defence") == 0)
                    {
                        this->reaDefence = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "territory") == 0)
                    {
                        this->territory = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "moveSpeed") == 0)
                    {
                        this->moveSpeed = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                }

                return;
            } //end if ==id
        }

    }  //end if ���ļ��п�
}

void CMonster::moveMyself(int** ppArrayScene)
{
    //���� �ƶ��ٶ� ʱ�� ȷ���Ƿ��ƶ� 
    DWORD dwCurTime = GetTickCount();
    if (dwCurTime - dwPreTime > (DWORD)moveSpeed)
    {
        dwPreTime = GetTickCount();  //����ʱ��

        //��ֹ ѭ������̫�� �� ��ѭ��
        int flagCount = 0;

        while (true)
        {
            //������ʱ������ȷ���ƶ�λ��
            CPosition tmpPos = CPosition(0, 0);

            switch ((rand() + rand()*rand()) % 4)
            {
            case 0:{tmpPos = curPos + DI_LEFT; break; }
            case 1:{tmpPos = curPos + DI_UP; break; }
            case 2:{tmpPos = curPos + DI_RIGHT; break; }
            case 3:{tmpPos = curPos + DI_DOWN; break; }
            default: break;
            }

            //�ж�Ŀ����Ƿ�����ƶ�
            if (ppArrayScene[tmpPos.getX()][tmpPos.getY()] == 0  //Ŀ����ǿյ�
                && tmpPos - prePos <= territory)                 //Ŀ���û�г���Ѳ�߷�Χ
            {
                curPos = tmpPos;
                return;
            }

            flagCount++;
            if (flagCount > 20)
            {
                //ѭ�� ���� ����ֱ���˳����ƶ�
                return;
            }
        }

    }
}

void CMonster::skillAttack1(CBasePerson**)
{

}

void CMonster::skillAttack2(CBasePerson**)
{

}

void CMonster::skillAttack3(CBasePerson**)
{

}


CPosition CMonster::findBasePos()
{
    //��ӡ��׼�� ��ս������ȷ��
    auto tmpScene = new CFightScene();

    //ȷ�������ӡ��
    int x = tmpScene->getScenePoint().getX() + orderNum * 5 + 1;
    int y = tmpScene->getStatePoint().getY()-17 ;

    CPosition tmpPos = CPosition(x, y);

    delete tmpScene;
    tmpScene = 0;

    return tmpPos;
}

void CMonster::printInfo()
{
    //�����û�ɫ
    if (curHP <= 0)
    {
        CUtils::setColor(120);
    }

    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();

    tmpPos.setY(tmpPos.getY() + 7);


    //�Ȳ��� ֮ǰ����Ϣ
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "                  ";

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "��" << name << "�� ";

    //��ӡ״̬
    for (auto itr = mapBuff.begin();
        itr != mapBuff.end();
        itr++)
    {
        if (itr->first == FB_ZHONGDU && itr->second > 0)
        {
            cout << "�ж� ";
        }

        if (itr->first == FB_XUANYUN && itr->second > 0)
        {
            cout << "ѣ�� ";
        }

    }

    //��ӡ HP 
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    printf_s("HP:%5d/%5d\n", curHP, maxHP);

    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    printf_s("MP:%5d/%5d\n", curMP, maxMP);

    //
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    printf_s("��/��:%4d/%4d\n", reaAttack, reaDefence);

    //����ɫ��ΪĬ��
    CUtils::setColor();
}

void CMonster::printBaseFace()
{
    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();

    //��ӡͼ��
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "  �q����r";
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    cout << " {/ o  o /} ";
    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    cout << "  ( (oo) )  ";
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    cout << "   ����   " << endl;
}

void CMonster::renderMyself()
{
    cout << "��";
}
