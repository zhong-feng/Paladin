#include "CMonster.h"

int CMonster::countNum=0;

CMonster::CMonster()
{
    isShow = true;

    monsterID = MI_NONE;

    moveSpeed = 0;
    dwPreTime = GetTickCount();  //获取当前创建时间

    orderNum = 0;
}

CMonster::~CMonster()
{

}


void CMonster::initMonsterPropOnXml(CMonsterID _ID)
{
    //文件路径
    char* filePath = ".\\Resource\\Config\\Monster.xml";

    //创建XML文件对象
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //解析文件
        //获取xml文件的根元素 (monsterSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //遍历每一个子元素 (monster)
        for (TiXmlElement* pMonsterElement = pSystemElement->FirstChildElement();
            pMonsterElement != nullptr;
            pMonsterElement = pMonsterElement->NextSiblingElement())
        {
            //根据 ID 找到相应的  (monster)
            if ((CMonsterID)atoi(pMonsterElement->FirstAttribute()->Value()) == _ID)
            {
                //遍历每一个子元素 (具体属性)
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

    }  //end if 打开文件判空
}

void CMonster::moveMyself(int** ppArrayScene)
{
    //根据 移动速度 时间 确认是否移动 
    DWORD dwCurTime = GetTickCount();
    if (dwCurTime - dwPreTime > (DWORD)moveSpeed)
    {
        dwPreTime = GetTickCount();  //更新时间

        //防止 循环次数太多 或 死循环
        int flagCount = 0;

        while (true)
        {
            //定义临时变量，确认移动位置
            CPosition tmpPos = CPosition(0, 0);

            switch ((rand() + rand()*rand()) % 4)
            {
            case 0:{tmpPos = curPos + DI_LEFT; break; }
            case 1:{tmpPos = curPos + DI_UP; break; }
            case 2:{tmpPos = curPos + DI_RIGHT; break; }
            case 3:{tmpPos = curPos + DI_DOWN; break; }
            default: break;
            }

            //判断目标点是否可以移动
            if (ppArrayScene[tmpPos.getX()][tmpPos.getY()] == 0  //目标点是空地
                && tmpPos - prePos <= territory)                 //目标点没有超出巡逻范围
            {
                curPos = tmpPos;
                return;
            }

            flagCount++;
            if (flagCount > 20)
            {
                //循环 次数 过多直接退出不移动
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
    //打印基准点 由战斗场景确定
    auto tmpScene = new CFightScene();

    //确定具体打印点
    int x = tmpScene->getScenePoint().getX() + orderNum * 5 + 1;
    int y = tmpScene->getStatePoint().getY()-17 ;

    CPosition tmpPos = CPosition(x, y);

    delete tmpScene;
    tmpScene = 0;

    return tmpPos;
}

void CMonster::printInfo()
{
    //死亡用灰色
    if (curHP <= 0)
    {
        CUtils::setColor(120);
    }

    //确定打印基准点
    auto tmpPos = findBasePos();

    tmpPos.setY(tmpPos.getY() + 7);


    //先擦除 之前的信息
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "                  ";

    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "【" << name << "】 ";

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

void CMonster::printBaseFace()
{
    //确定打印基准点
    auto tmpPos = findBasePos();

    //打印图像
    CUtils::gotoXY(tmpPos.getX(), tmpPos.getY() * 2);
    cout << "  ╭︿︿︿╮";
    CUtils::gotoXY(tmpPos.getX() + 1, tmpPos.getY() * 2);
    cout << " {/ o  o /} ";
    CUtils::gotoXY(tmpPos.getX() + 2, tmpPos.getY() * 2);
    cout << "  ( (oo) )  ";
    CUtils::gotoXY(tmpPos.getX() + 3, tmpPos.getY() * 2);
    cout << "   ︶︶︶   " << endl;
}

void CMonster::renderMyself()
{
    cout << "怪";
}
