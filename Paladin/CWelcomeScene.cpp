#include "CWelcomeScene.h"


void CWelcomeScene::initPropsOnSceneArray()
{
}

void CWelcomeScene::renderSceneUI()
{
}

void CWelcomeScene::downChoice(int& _choice)
{
    //擦除箭头
    eraserFlagChoice(_choice);

    _choice++;
    if (_choice > 2)
    {
        _choice = 0;
    }

    renderFlagChoice(_choice);
}

void CWelcomeScene::upChoice(int& _choice)
{
    //擦除箭头
    eraserFlagChoice(_choice);

    _choice--;
    if (_choice < 0)
    {
        _choice = 2;
    }

    renderFlagChoice(_choice);
}

void CWelcomeScene::eraserFlagChoice(int _choice)
{
    CPosition tmpPos = describePoint + CPosition(_choice, -2);

    CUtils::setColor();
    CUtils::gotoXY(tmpPos);
    cout << "   ";
}

void CWelcomeScene::renderFlagChoice(int _choice)
{
    CPosition tmpPos = describePoint + CPosition(_choice, -2);

    CUtils::setColor(79);
    CUtils::gotoXY(tmpPos);
    cout << " →";

    CUtils::setColor();
}

void CWelcomeScene::rendChoice()
{
    CPosition tmpPos = describePoint;

    //确定颜色
    CUtils::setColor(12);

    //定位坐标
    CUtils::gotoXY(tmpPos);
    cout << "新游戏";

    tmpPos = tmpPos + DI_DOWN;
    CUtils::gotoXY(tmpPos);
    cout << "旧的回忆";

    tmpPos = tmpPos + DI_DOWN;
    CUtils::gotoXY(tmpPos);
    cout << "退出";

    CUtils::setColor();
}

void CWelcomeScene::renderRoler()
{
    static int baseY = 0;

    int tmpY = baseY;

    CPosition tmpPos = statePoint + scenePoint;

    for (int j = 0; j < helpPoint.getY() - statePoint.getY() - 1; tmpY++, j++)
    {
        for (int i = 0; i < helpPoint.getX() - statePoint.getX() - 2; i++)
        {
            if (tmpY >= width)
            {
                tmpY = 0;
            }
            //定位坐标
            CUtils::gotoXY(tmpPos.getX() + i + 1, (tmpPos.getY() + j) * 2);
            if (ppSceneArray[i][tmpY] == 1)
            {
                //确定边框颜色
                CUtils::setColor(111);
                cout << "■";
            }
            else
            {
                //打印空白
                CUtils::setColor();
                cout << "  ";
            }
        }
    }

    baseY++;
    if (baseY >= width)
    {
        baseY = 0;
    }

    CUtils::setColor();
}

void CWelcomeScene::renderBoder()
{
    //确定边框位置
    for (int i = 0; i < MAXCOL; i++)
    {
        for (int j = 0; j < MAXROW + 5 - 1; j++)
        {
            if (i == 0 || i == MAXCOL - 1 || j == 0 || j == MAXROW + 5 - 2)
            {
                //确定边框颜色
                CUtils::setColor(ColorOfBorder);

                //定位坐标
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "◆";

                continue;
            }

            if (((i == statePoint.getX() || i == helpPoint.getX()) && (j >= statePoint.getY() && j <= helpPoint.getY()))
                || ((j == statePoint.getY() || j == helpPoint.getY()) && (i >= statePoint.getX() && i <= helpPoint.getX())))
            {
                //确定边框颜色
                CUtils::setColor(111);

                //定位坐标
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "★";

                continue;
            }

        }
    }

    CUtils::setColor();
}

int CWelcomeScene::enterUIScene()
{
    //播放场景背景音乐
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\welcome.wav");

    //打印 边框
    renderBoder();

    //打印游戏选择
    rendChoice();

    //默认选择第一个选项
    int choiceNum = 0;
    renderFlagChoice(choiceNum);


    while (true)
    {
        static DWORD dwPreTime = GetTickCount();  //previous 先前的  -- 静态局部变量
        DWORD dwCurTime = GetTickCount();
        if (dwCurTime - dwPreTime > 500)
        {
            dwPreTime = GetTickCount();
            renderRoler();
        }


        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
            case 'W':{ upChoice(choiceNum); break; }
            case 's':
            case 'S':{ downChoice(choiceNum); break; }

            case '\r':
            {
                switch (choiceNum)
                {
                case 2:
                case 1:
                case 0:return CI_Scene1TOBirth;
                default: break;
                }
                break;
            }

            case 27:{ return -1; break; }

            default: break;
            }
        }


    }

    return CI_Scene1TOBirth;
}

CWelcomeScene::~CWelcomeScene()
{

}

CWelcomeScene::CWelcomeScene()
{
    height = 13;
    width = 42;

    //动态分配 场景 地图
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height*sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //根据txt文件初始化场景数组
    initUISceneArrayOnTextFile("WelcomeScene");

    //更换特殊点坐标点
    statePoint = CPosition(3, 5);
    helpPoint = statePoint + CPosition(14, 25);
    describePoint = CPosition(23, 22);
}
