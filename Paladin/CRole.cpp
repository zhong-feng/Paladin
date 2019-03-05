#include "CRole.h"


CRole::CRole()
{
    level = 0;
    curEXP = maxEXP = 0;

    strength = 0;
    agility = 0;
    intelligence = 0;

    basicAttack = 0;
    basicDefence = 0;

    skillDescribe[0] = "";
    skillDescribe[1] = "";
    skillDescribe[2] = "";

    posOfScene = RS_NONE;
    weaponID = ID_None;
    garmentID = ID_None;

}

CRole::~CRole()
{

}

void CRole::printInfo()
{
    //�����û�ɫ
    if (curHP <= 0)
    {
        CUtils::setColor(120);
    }

    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();

    //�Ȳ��� ֮ǰ����Ϣ
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "               ";

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << name<<" ";

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

void CRole::initMonsterPropOnXml(CRoleID _ID)
{
    //�ļ�·��
    char* filePath = ".\\Resource\\Config\\Role.xml";

    //����XML�ļ�����
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //�����ļ�
        //��ȡxml�ļ��ĸ�Ԫ�� (roleSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //����ÿһ����Ԫ�� (monster)
        for (TiXmlElement* proleElement = pSystemElement->FirstChildElement();
            proleElement != nullptr;
            proleElement = proleElement->NextSiblingElement())
        {
            //���� ID �ҵ���Ӧ��  (monster)
            if ((CRoleID)atoi(proleElement->FirstAttribute()->Value()) == _ID)
            {
                //����ÿһ����Ԫ�� (��������)
                for (TiXmlElement* pAttributeElement = proleElement->FirstChildElement();
                    pAttributeElement != nullptr;
                    pAttributeElement = pAttributeElement->NextSiblingElement())
                {
                    if (strcmp(pAttributeElement->Value(), "name") == 0)
                    {
                        this->name = pAttributeElement->FirstChild()->ToText()->Value();
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "strength") == 0)
                    {
                        this->strength = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "agility") == 0)
                    {
                        this->agility = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "intelligence") == 0)
                    {
                        this->intelligence = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "basicAttack") == 0)
                    {
                        this->basicAttack = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                    if (strcmp(pAttributeElement->Value(), "basicDefence") == 0)
                    {
                        this->basicDefence = atoi(pAttributeElement->FirstChild()->ToText()->Value());
                        continue;
                    }

                }

                return;
            } //end if ==id
        }

    }  //end if ���ļ��п�
}

CPosition CRole::findBasePos()
{
    //��ӡ��׼�� ��ս������ȷ��
    auto tmpScene = new CFightScene();
    auto tmpPos = tmpScene->getScenePoint();

    delete tmpScene;
    tmpScene = 0;

    //ȷ�������ӡ��
    switch (posOfScene)
    {
    case RS_TWO:{tmpPos.setX(tmpPos.getX() + 8); break; }
    default: break;
    }

    tmpPos = tmpPos + CPosition(3, 1);

    return tmpPos;
}

void CRole::renderSkill()
{
    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 15);

    //��ӡ�����б�
    CUtils::gotoXY(tmpPos);
    cout << "��ͨ����" << endl;

    for (int i = 0; i < MAXSKILLNUM; i++)
    {
        if (skillNameArray[i] != "")
        {
            if (curMP < skillUseMPArray[i])
            {
                //MP ���㣬��ɫ��ʾ
                CUtils::setColor(8);
            }

            CUtils::gotoXY(tmpPos.getX() + 1 + i, tmpPos.getY() * 2);
            cout << skillNameArray[i] << endl;

            CUtils::setColor();
        }
    }

    CUtils::gotoXY(tmpPos.getX() + 4, tmpPos.getY() * 2);
    cout << "ʹ����Ʒ" << endl;
}

int CRole::choiceSkill()
{
    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 14);

    int choiceNum = 0;

    //����ͨ����ǰ���ӡ��ɫ��ͷ
    CUtils::setColor(79);
    CUtils::gotoXY(tmpPos);
    cout << "��" << endl;

    CUtils::setColor();

    while (true)
    {
        char keyCode = _getch();

        switch (keyCode)
        {
        case 'w':
        case 'W':{ upFlagSkill(choiceNum, tmpPos); break; }
        case 's':
        case 'S':{ downFlagSkill(choiceNum, tmpPos);  break; }
        case '\r':{ return choiceNum; break; }
        default: break;
        }

        //��ӡ����˵��
        describeSkill(choiceNum);
    }
}

void CRole::upFlagSkill(int& choiceNum, CPosition _bacePos)
{
    //������ǰ��ͷ
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "  " << endl;

    for (int i = 0; i < 5; i++)
    {
        choiceNum--;
        if (choiceNum < 0)
        {
            choiceNum = 4;
        }

        //ѡ����ͨ����
        if (choiceNum == 0)
        {
            break;
        }

        //ѡ��ʹ��ҩƷ
        if (choiceNum == 4)
        {
            break;
        }

        //���� ��Ҫ����Ҫ��
        if (curMP < skillUseMPArray[choiceNum - 1])
        {
            continue;
        }
        else
        {
            break;
        }
    }

    //��ӡ��ѡ ���� ��ͷ
    CUtils::setColor(79);
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "��" << endl;

    CUtils::setColor();
}

void CRole::downFlagSkill(int& choiceNum, CPosition _bacePos)
{
    //������ǰ��ͷ
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "  " << endl;

    for (int i = 0; i < 5 + 1; i++)
    {
        choiceNum++;
        if (choiceNum > 4)
        {
            choiceNum = 0;
        }

        //ѡ����ͨ����
        if (choiceNum == 0)
        {
            break;
        }

        //ѡ��ʹ��ҩƷ
        if (choiceNum == 4)
        {
            break;
        }

        //���� ��Ҫ����Ҫ��
        if (curMP < skillUseMPArray[choiceNum - 1])
        {
            continue;
        }
        else
        {
            break;
        }

    }

    //��ӡ��ѡ ���� ��ͷ
    CUtils::setColor(79);
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "��" << endl;

    CUtils::setColor();
}

void CRole::eraseSkill(int _choiceSkillNum)
{
    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 15);

    //���������б� ǰ��ļ�ͷ
    CUtils::gotoXY(tmpPos.getX() + _choiceSkillNum, (tmpPos.getY() - 1) * 2);
    cout << "  " << endl;

    //������ͨ����
    CUtils::gotoXY(tmpPos);
    cout << "        " << endl;

    //�������ܹ���
    for (int i = 0; i < MAXSKILLNUM; i++)
    {

        CUtils::gotoXY(tmpPos.getX() + 1 + i, tmpPos.getY() * 2);
        cout << "          " << endl;
        
    }

    //����ʹ��ҩƷ
    CUtils::gotoXY(tmpPos.getX() + 4, tmpPos.getY() * 2);
    cout << "          " << endl;
}

void CRole::describeSkill(int _choiceNum)
{
    //ȷ��˵����׼�� ��ս������ȷ��
    auto tmpScene = new CFightScene();
    auto describePos = tmpScene->getDescribePoint();

    //��Χ���¿�϶
    describePos.setX(describePos.getX() + 1);
    describePos.setY(describePos.getY() + 3);

    delete tmpScene;
    tmpScene = 0;

    //��������˵������(ÿ�� 25 ���� )
    CUtils::gotoXY(describePos.getX(), describePos.getY() * 2);
    cout << "                                                  ";
    CUtils::gotoXY(describePos.getX() + 1, describePos.getY() * 2);
    cout << "                                                  ";
    CUtils::gotoXY(describePos.getX() + 2, describePos.getY() * 2);
    cout << "                                                  ";

    //ȷ���������
    string tmpStr = "";
    switch (_choiceNum)
    {
    case 0:{tmpStr = "��ͨ��������Ŀ�����һ���˺�"; break; }
    case 1:{tmpStr = skillDescribe[0]; break; }
    case 2:{tmpStr = skillDescribe[1]; break; }
    case 3:{tmpStr = skillDescribe[2]; break; }
    case 4:{tmpStr = "ʹ�ñ����е�ҩƷ"; break; }
    default:
        break;
    }

    //ȷ�� ��ʼ ���λ��
    CUtils::gotoXY(describePos);
    for (unsigned int i = 0; i < tmpStr.length(); i++)
    {
        //����#����
        if (tmpStr[i] == '#')
        {
            describePos = describePos + DI_DOWN;
            CUtils::gotoXY(describePos);

            continue;
        }

        cout << tmpStr[i];

    }
}

void CRole::printBaseFace()
{
    //ȷ����ӡ��׼��
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 8);

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "    ___ " << endl;
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    cout << "  //���" << endl;
    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    cout << "  c @ @ " << endl;
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    cout << "  \\ ~// " << endl;
}


CBasePerson** CRole::choicePerson(CBasePerson** _person, bool isMonster)
{
    //��������ȷ����ѡ���ֵ
    int maxChoiceNum = 0;
    if (isMonster)
    {
        maxChoiceNum = CMonster::countNum;
    }
    else
    {
        maxChoiceNum = 2;
    }

    //���� ѡ��Ŀ������
    int choiceNum = 0;

    //Ĭ��ѡ��һ������ ��ɫͼ���ʾѡ��
    for (int i = 0; i < maxChoiceNum; i++)
    {
        if (_person[i]->getCurHP() > 0)
        {
            choiceNum = i;

            CUtils::setColor(193);
            _person[i]->printBaseFace();

            CUtils::setColor();

            break;
        }
    }

    while (true)
    {
        char keyCode = _getch();

        switch (keyCode)
        {
        case 'w':
        case 'W': { upFlagPerson(choiceNum, _person, maxChoiceNum); break; }
        case 's':
        case 'S': {  downFlagPerson(choiceNum, _person, maxChoiceNum);  break; }
        case '\r':
        {
            //����ǰѡ��Ŀ���Ϊ����
            _person[choiceNum]->printFace();

            return _person + choiceNum;
            break;
        }
        default: break;
        }

    }
}

void CRole::upFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum)
{
    //����ǰѡ��Ŀ���Ϊ����
    _person[_choiceNum]->printFace();

    for (int i = 0; i < _maxNum; i++)
    {
        //��� -1
        _choiceNum--;

        if (_choiceNum < 0)
        {
            _choiceNum = _maxNum - 1;
        }

        if (_person[_choiceNum]->getCurHP() > 0 && _person[_choiceNum]->getIsShow() == true)
        {
            CUtils::setColor(193);
            _person[_choiceNum]->printBaseFace();

            CUtils::setColor();

            return;
        }
    }

}

void CRole::downFlagPerson(int& _choiceNum, CBasePerson** _person, int _maxNum)
{

    //����ǰѡ��Ŀ���Ϊ����
    _person[_choiceNum]->printFace();

    for (int i = 0; i < _maxNum; i++)
    {
        //��� +1
        _choiceNum++;

        if (_choiceNum == _maxNum)
        {
            _choiceNum = 0;
        }

        if (_person[_choiceNum]->getCurHP() > 0 && _person[_choiceNum]->getIsShow() == true)
        {
            CUtils::setColor(193);
            _person[_choiceNum]->printBaseFace();

            CUtils::setColor();

            return;
        }
    }
}

