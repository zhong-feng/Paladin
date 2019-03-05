#include "CScene.h"
#include "CItemFactory.h"
#include "CBagDirector.h"

CScene::CScene()
{
    sceneID = SI_None;
    name = "";

    height = 0;
    width = 0;

    ppSceneArray = 0;

    player = CPlayer();

    basePos = CPosition(0, 0);

    dwPreMessage = GetTickCount();

    //确定场景位置
    scenePoint = CPosition(BASESCENEPOSX, BASESCENEPOSY);
    statePoint = CPosition(BASESCENEPOSX, BASESCENEPOSY + ROWOFSCENE+1);
    describePoint = CPosition(BASESCENEPOSX + COLOFSCENE +1, BASESCENEPOSY);
    helpPoint = CPosition(BASESCENEPOSX+ COLOFSCENE/2, BASESCENEPOSY + ROWOFSCENE + 1);
}

CScene::~CScene()
{
    if (ppSceneArray) //先判空
    {
        for (int i = 0; i < height; i++)
        {
            delete[] ppSceneArray[i];
            ppSceneArray[i] = 0;
        }

        delete[] ppSceneArray;
        ppSceneArray = 0;
    }
}

void CScene::initUISceneArrayOnTextFile(string _name)
{
    //确认文件路径
    string filePath = ".\\Resource\\Scene\\";
    filePath = filePath + _name + ".txt";

    //打开文件
    FILE* pFile = 0;
    fopen_s(&pFile, filePath.c_str(), "r");

    //判空
    if (pFile == nullptr)
    {
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fscanf_s(pFile, "%d ", &ppSceneArray[i][j]);
        }
    }

    //关闭文件
    fclose(pFile);
    pFile = 0;
}

void CScene::setValueOfSceneArrayOnPos(CPosition position, int value)
{
    if (position.getX() < 0 || position.getX() >= width
        || position.getY() < 0 || position.getY() >= height)
    {
        return;
    }

    ppSceneArray[position.getX()][position.getY()] = value;
}

int CScene::getValueOfSceneArrayOnPos(CPosition position)
{
    if (position.getX() < 0 || position.getX() >=  height
        || position.getY() < 0 || position.getY() >= width)
    {
        return -1;
    }

    return ppSceneArray[position.getX()][position.getY()];
}

void CScene::renderBoder()
{
    //打印场景名

    //确定 颜色
    CUtils::setColor(12);

    //定位坐标
    CUtils::gotoXY(scenePoint.getX() - 3, (scenePoint.getY() +2) * 2);

    cout << name << endl;

    //打印边框

    //确定边框颜色
    CUtils::setColor(ColorOfBorder);

    //确定边框位置
    for (int i = 0; i < MAXCOL; i++)
    {
        for (int j = 0; j < MAXROW; j++)
        {
            if (i == 0 || i == COLOFSCENE + 1 || i == MAXCOL - 1
                || j == 0 || j == MAXROW - 1 || (j == ROWOFSCENE + 1 && i < COLOFSCENE + 1))
            {
                //定位坐标
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "◆";
            }

        }
    }

    //将颜色改为默认值
    CUtils::setColor();
}

void CScene::rendScenePlayer()
{
    //定义临时坐标点 确认玩家  相对位置
    CPosition tmpPos = CPosition(0, 0);

    //确认玩家  相对位置 x
    if (player.getPos().getX() - basePos.getX() < COLOFSCENE / 2)
    {
        tmpPos.setX(player.getPos().getX());
    }
    else if (player.getPos().getX() - basePos.getX() > COLOFSCENE / 2)
    {
        tmpPos.setX(player.getPos().getX() - basePos.getX());
    }
    else
    {
        tmpPos.setX(COLOFSCENE / 2);
    }

    //确认玩家  相对位置 y
    if (player.getPos().getY() - basePos.getY() < ROWOFSCENE / 2)
    {
        tmpPos.setY(player.getPos().getY());
    }
    else if (player.getPos().getY() - basePos.getY() > ROWOFSCENE / 2)
    {
        tmpPos.setY(player.getPos().getY() - basePos.getY());
    }
    else
    {
        tmpPos.setY(COLOFSCENE / 2);
    }

    //相对位置 + 渲染框基准点 = 玩家的实际位置
    tmpPos = tmpPos + scenePoint;

    CUtils::gotoXY(tmpPos);

    //调用玩家的 渲染方法
    player.scenePlayer();

    //打印玩家坐标
    rendPlayerPos();
}

void CScene::renderHelpInfo()
{
    //设定颜色
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
    cout << "      帮助信息";

    CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
    cout << "  移动: 上   W/w";

    CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
    cout << "        下   S/s";

    CUtils::gotoXY(helpPoint.getX() + 4, helpPoint.getY() * 2);
    cout << "        左   A/a";

    CUtils::gotoXY(helpPoint.getX() + 5, helpPoint.getY() * 2);
    cout << "        右   D/d";

    CUtils::gotoXY(helpPoint.getX() + 7, helpPoint.getY() * 2);
   cout << "  菜单       B/b";

    CUtils::gotoXY(helpPoint.getX() + 8, helpPoint.getY() * 2);
    cout << "  退出       Esc";

    //颜色改回默认值
    CUtils::setColor();
}

void CScene::rendPlayerPos()
{
    CUtils::gotoXY(statePoint.getX() + 1, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "      当前坐标";

    CUtils::gotoXY(statePoint.getX() + 3, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "    行     ";
    CUtils::setColor(12);
    cout << player.getPos().getX();



    CUtils::gotoXY(statePoint.getX() + 4, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "    列     ";
    CUtils::setColor(12);
    cout << player.getPos().getY();

    CUtils::setColor();
}

bool CScene::setBasePosByBirthPos()
{
    //玩家必须有位置
    if (player.getPos().getX() == 0 || player.getPos().getY() == 0)
    {
        return false;
    }

    //确定基准点 x 坐标
    if (player.getPos().getX() - COLOFSCENE / 2 <= 0)
    {
        basePos.setX(0);
    }
    else if (player.getPos().getX() + COLOFSCENE / 2 >= height)
    {
        basePos.setX(height - COLOFSCENE);
    }
    else
    {
        basePos.setX(player.getPos().getX() - COLOFSCENE / 2);
    }

    //确定基准点 y 坐标
    if (player.getPos().getY() - ROWOFSCENE / 2 <= 0)
    {
        basePos.setY(0);
    }
    else if (player.getPos().getY() + ROWOFSCENE / 2 >= width)
    {
        basePos.setY(width - ROWOFSCENE);
    }
    else
    {
        basePos.setY(player.getPos().getY() - ROWOFSCENE / 2);
    }

    return true;
}

void CScene::renderMessage(const char* str)
{
    //消除之前的渲染
    dwPreMessage = 0;
    eraserMessage();

    //记录消息时间
    dwPreMessage = GetTickCount();
    //确定打印颜色
    CUtils::setColor(10);

    auto tmpPos = describePoint+CPosition(1,1);
    CUtils::gotoXY(tmpPos);
    while (*str!='\0')
    {
        if (*str == '#')
        {
            tmpPos = tmpPos + DI_DOWN;
            CUtils::gotoXY(tmpPos);

            str++;
            continue;
        }

        cout << *str;
        str++;
    }

    CUtils::setColor();
}

void CScene::eraserMessage()
{
    if (GetTickCount() - dwPreMessage < 5000)
    {
        return;
    }

    auto tmpPos = describePoint;

    for (int i = 0; i < 4; i++)
    {
        CUtils::gotoXY(tmpPos);
        cout << "                                                   ";
        tmpPos = tmpPos + DI_DOWN;
    }


    //清空消息栏后 将时间设为最大值（简单认为），不再触发清空
    dwPreMessage = GetTickCount() * 10;
}

void CScene::dropItem()
{
    //获得金钱
    int tmpMoney = 1000;

    //获得物品
    CItemID tmpItem = ID_None;
    int randomItem = (rand()*rand() + rand()) % 7;

    switch (randomItem)
    {
    case 0: { tmpItem = ID_HP;  break; }
    case 1: { tmpItem = ID_MP; break; }
    case 2: { tmpItem = ID_Sword; break; }
    case 3: { tmpItem = ID_Whips;  break; }
    case 4: { tmpItem = ID_Ioricae; break; }
    case 5: { tmpItem = ID_Sackcloth; break; }
    case 6: { tmpItem = ID_Apple; }
    default: break;
    }

    //将物品放入背包
    CBagDirector::getInstance()->setMoney(CBagDirector::getInstance()->getMoney() + tmpMoney);
    CBagDirector::getInstance()->getBag()->addItem(tmpItem);

    char buffer[10] = { 0 };
    _itoa_s(tmpMoney, buffer, 10);
    string tmpStr = "恭喜你获得：#金钱  ";
    tmpStr = tmpStr + buffer + "#物品  ";

    auto pTmpItem = CItemFactory::createItem((CItemID)tmpItem);

    tmpStr = tmpStr + pTmpItem->name;

    delete pTmpItem;
    pTmpItem = 0;

    renderMessage(tmpStr.c_str());
}
