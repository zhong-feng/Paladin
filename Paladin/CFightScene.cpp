#include "CFightScene.h"


void CFightScene::initPropsOnSceneArray()
{

}

void CFightScene::renderSceneUI()
{

}

int CFightScene::enterUIScene()
{
    //清空打印
    system("cls");

    //打印边框
    renderBoder();

    //打印帮助信息
    renderHelpInfo();

    return 0;
}

void CFightScene::renderBoder()
{
    //确定边框颜色
    CUtils::setColor(ColorOfBorder);

    //确定边框位置
    for (int i = 0; i < describePoint.getX()+ FIGHTDESRIBEPOINTWIDE; i++)
    {
        for (int j = 0; j < statePoint.getY()+ FIGHTSTATEPOINTWIDE; j++)
        {
            if (i == 0 || i == describePoint.getX() + FIGHTDESRIBEPOINTWIDE - 1
                || j == 0 || j == statePoint.getY() + FIGHTSTATEPOINTWIDE -1
                || (i == describePoint.getX()-1 && j < statePoint.getY() - 1)
                || j == statePoint.getY()-1)
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

CFightScene::CFightScene()
{
    scenePoint = CPosition(1, 1);
    statePoint = CPosition(1, 40);
    describePoint = CPosition(24, 1);
    helpPoint = CPosition(20, 40);
}

void CFightScene::renderHelpInfo()
{
    //设定颜色
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
    cout << "           帮助信息";

    CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
    cout << "     光标移动: 上   W/w";

    CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
    cout << "               下   S/s";

    CUtils::gotoXY(helpPoint.getX() + 5, helpPoint.getY() * 2);
    cout << "       确认       Enter";

    //颜色改回默认值
    CUtils::setColor();
}

CFightScene::~CFightScene()
{

}
