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
    //死亡用灰色
    if (curHP <= 0)
    {
        CUtils::setColor(120);
    }

    //确定打印基准点
    auto tmpPos = findBasePos();

    //先擦除 之前的信息
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "               ";

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << name<<" ";

    //打印状态
    for (auto itr = mapBuff.begin();
        itr != mapBuff.end();
        itr++)
    {
        if (itr->first == FB_ZHONGDU && itr->second > 0)
        {
            cout << "中毒 ";
        }

        if (itr->first == FB_XUANYUN && itr->second > 0)
        {
            cout << "眩晕 ";
        }

    }

    //打印 HP 
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    printf_s("HP:%5d/%5d\n", curHP, maxHP);

    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    printf_s("MP:%5d/%5d\n", curMP, maxMP);

    //
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    printf_s("攻/防:%4d/%4d\n", reaAttack, reaDefence);

    //将颜色改为默认
    CUtils::setColor();
}

void CRole::initMonsterPropOnXml(CRoleID _ID)
{
    //文件路径
    char* filePath = ".\\Resource\\Config\\Role.xml";

    //创建XML文件对象
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //解析文件
        //获取xml文件的根元素 (roleSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //遍历每一个子元素 (monster)
        for (TiXmlElement* proleElement = pSystemElement->FirstChildElement();
            proleElement != nullptr;
            proleElement = proleElement->NextSiblingElement())
        {
            //根据 ID 找到相应的  (monster)
            if ((CRoleID)atoi(proleElement->FirstAttribute()->Value()) == _ID)
            {
                //遍历每一个子元素 (具体属性)
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

    }  //end if 打开文件判空
}

CPosition CRole::findBasePos()
{
    //打印基准点 由战斗场景确定
    auto tmpScene = new CFightScene();
    auto tmpPos = tmpScene->getScenePoint();

    delete tmpScene;
    tmpScene = 0;

    //确定具体打印点
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
    //确定打印基准点
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 15);

    //打印技能列表
    CUtils::gotoXY(tmpPos);
    cout << "普通攻击" << endl;

    for (int i = 0; i < MAXSKILLNUM; i++)
    {
        if (skillNameArray[i] != "")
        {
            if (curMP < skillUseMPArray[i])
            {
                //MP 不足，灰色显示
                CUtils::setColor(8);
            }

            CUtils::gotoXY(tmpPos.getX() + 1 + i, tmpPos.getY() * 2);
            cout << skillNameArray[i] << endl;

            CUtils::setColor();
        }
    }

    CUtils::gotoXY(tmpPos.getX() + 4, tmpPos.getY() * 2);
    cout << "使用物品" << endl;
}

int CRole::choiceSkill()
{
    //确定打印基准点
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 14);

    int choiceNum = 0;

    //在普通攻击前面打印红色箭头
    CUtils::setColor(79);
    CUtils::gotoXY(tmpPos);
    cout << "→" << endl;

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

        //打印技能说明
        describeSkill(choiceNum);
    }
}

void CRole::upFlagSkill(int& choiceNum, CPosition _bacePos)
{
    //擦除当前箭头
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "  " << endl;

    for (int i = 0; i < 5; i++)
    {
        choiceNum--;
        if (choiceNum < 0)
        {
            choiceNum = 4;
        }

        //选择普通攻击
        if (choiceNum == 0)
        {
            break;
        }

        //选择使用药品
        if (choiceNum == 4)
        {
            break;
        }

        //技能 需要满足要求
        if (curMP < skillUseMPArray[choiceNum - 1])
        {
            continue;
        }
        else
        {
            break;
        }
    }

    //打印所选 技能 箭头
    CUtils::setColor(79);
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "→" << endl;

    CUtils::setColor();
}

void CRole::downFlagSkill(int& choiceNum, CPosition _bacePos)
{
    //擦除当前箭头
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "  " << endl;

    for (int i = 0; i < 5 + 1; i++)
    {
        choiceNum++;
        if (choiceNum > 4)
        {
            choiceNum = 0;
        }

        //选择普通攻击
        if (choiceNum == 0)
        {
            break;
        }

        //选择使用药品
        if (choiceNum == 4)
        {
            break;
        }

        //技能 需要满足要求
        if (curMP < skillUseMPArray[choiceNum - 1])
        {
            continue;
        }
        else
        {
            break;
        }

    }

    //打印所选 技能 箭头
    CUtils::setColor(79);
    CUtils::gotoXY(_bacePos.getX() + choiceNum, _bacePos.getY() * 2);
    cout << "→" << endl;

    CUtils::setColor();
}

void CRole::eraseSkill(int _choiceSkillNum)
{
    //确定打印基准点
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 15);

    //擦除技能列表 前面的箭头
    CUtils::gotoXY(tmpPos.getX() + _choiceSkillNum, (tmpPos.getY() - 1) * 2);
    cout << "  " << endl;

    //擦除普通攻击
    CUtils::gotoXY(tmpPos);
    cout << "        " << endl;

    //擦除技能攻击
    for (int i = 0; i < MAXSKILLNUM; i++)
    {

        CUtils::gotoXY(tmpPos.getX() + 1 + i, tmpPos.getY() * 2);
        cout << "          " << endl;
        
    }

    //擦除使用药品
    CUtils::gotoXY(tmpPos.getX() + 4, tmpPos.getY() * 2);
    cout << "          " << endl;
}

void CRole::describeSkill(int _choiceNum)
{
    //确定说明基准点 由战斗场景确定
    auto tmpScene = new CFightScene();
    auto describePos = tmpScene->getDescribePoint();

    //周围留下空隙
    describePos.setX(describePos.getX() + 1);
    describePos.setY(describePos.getY() + 3);

    delete tmpScene;
    tmpScene = 0;

    //擦除技能说明区域(每行 25 个字 )
    CUtils::gotoXY(describePos.getX(), describePos.getY() * 2);
    cout << "                                                  ";
    CUtils::gotoXY(describePos.getX() + 1, describePos.getY() * 2);
    cout << "                                                  ";
    CUtils::gotoXY(describePos.getX() + 2, describePos.getY() * 2);
    cout << "                                                  ";

    //确定输出内容
    string tmpStr = "";
    switch (_choiceNum)
    {
    case 0:{tmpStr = "普通攻击，对目标造成一定伤害"; break; }
    case 1:{tmpStr = skillDescribe[0]; break; }
    case 2:{tmpStr = skillDescribe[1]; break; }
    case 3:{tmpStr = skillDescribe[2]; break; }
    case 4:{tmpStr = "使用背包中的药品"; break; }
    default:
        break;
    }

    //确认 初始 输出位置
    CUtils::gotoXY(describePos);
    for (unsigned int i = 0; i < tmpStr.length(); i++)
    {
        //遇到#换行
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
    //确定打印基准点
    auto tmpPos = findBasePos();
    tmpPos.setY(tmpPos.getY() + 8);

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "    ___ " << endl;
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    cout << "  //●●" << endl;
    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    cout << "  c @ @ " << endl;
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    cout << "  \\ ~// " << endl;
}


CBasePerson** CRole::choicePerson(CBasePerson** _person, bool isMonster)
{
    //根据类型确定可选最大值
    int maxChoiceNum = 0;
    if (isMonster)
    {
        maxChoiceNum = CMonster::countNum;
    }
    else
    {
        maxChoiceNum = 2;
    }

    //定义 选择目标的序号
    int choiceNum = 0;

    //默认选中一个对象 红色图像表示选中
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
            //将当前选中目标改为正常
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
    //将当前选中目标改为正常
    _person[_choiceNum]->printFace();

    for (int i = 0; i < _maxNum; i++)
    {
        //序号 -1
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

    //将当前选中目标改为正常
    _person[_choiceNum]->printFace();

    for (int i = 0; i < _maxNum; i++)
    {
        //序号 +1
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

