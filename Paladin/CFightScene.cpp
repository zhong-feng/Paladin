#include "CFightScene.h"


void CFightScene::initPropsOnSceneArray()
{

}

void CFightScene::renderSceneUI()
{

}

int CFightScene::enterUIScene()
{
    //��մ�ӡ
    system("cls");

    //��ӡ�߿�
    renderBoder();

    //��ӡ������Ϣ
    renderHelpInfo();

    return 0;
}

void CFightScene::renderBoder()
{
    //ȷ���߿���ɫ
    CUtils::setColor(ColorOfBorder);

    //ȷ���߿�λ��
    for (int i = 0; i < describePoint.getX()+ FIGHTDESRIBEPOINTWIDE; i++)
    {
        for (int j = 0; j < statePoint.getY()+ FIGHTSTATEPOINTWIDE; j++)
        {
            if (i == 0 || i == describePoint.getX() + FIGHTDESRIBEPOINTWIDE - 1
                || j == 0 || j == statePoint.getY() + FIGHTSTATEPOINTWIDE -1
                || (i == describePoint.getX()-1 && j < statePoint.getY() - 1)
                || j == statePoint.getY()-1)
            {
                //��λ����
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "��";
            }

        }

    }

    //����ɫ��ΪĬ��ֵ
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
    //�趨��ɫ
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
    cout << "           ������Ϣ";

    CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
    cout << "     ����ƶ�: ��   W/w";

    CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
    cout << "               ��   S/s";

    CUtils::gotoXY(helpPoint.getX() + 5, helpPoint.getY() * 2);
    cout << "       ȷ��       Enter";

    //��ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

CFightScene::~CFightScene()
{

}
