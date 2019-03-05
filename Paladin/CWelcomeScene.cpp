#include "CWelcomeScene.h"


void CWelcomeScene::initPropsOnSceneArray()
{
}

void CWelcomeScene::renderSceneUI()
{
}

void CWelcomeScene::downChoice(int& _choice)
{
    //������ͷ
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
    //������ͷ
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
    cout << " ��";

    CUtils::setColor();
}

void CWelcomeScene::rendChoice()
{
    CPosition tmpPos = describePoint;

    //ȷ����ɫ
    CUtils::setColor(12);

    //��λ����
    CUtils::gotoXY(tmpPos);
    cout << "����Ϸ";

    tmpPos = tmpPos + DI_DOWN;
    CUtils::gotoXY(tmpPos);
    cout << "�ɵĻ���";

    tmpPos = tmpPos + DI_DOWN;
    CUtils::gotoXY(tmpPos);
    cout << "�˳�";

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
            //��λ����
            CUtils::gotoXY(tmpPos.getX() + i + 1, (tmpPos.getY() + j) * 2);
            if (ppSceneArray[i][tmpY] == 1)
            {
                //ȷ���߿���ɫ
                CUtils::setColor(111);
                cout << "��";
            }
            else
            {
                //��ӡ�հ�
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
    //ȷ���߿�λ��
    for (int i = 0; i < MAXCOL; i++)
    {
        for (int j = 0; j < MAXROW + 5 - 1; j++)
        {
            if (i == 0 || i == MAXCOL - 1 || j == 0 || j == MAXROW + 5 - 2)
            {
                //ȷ���߿���ɫ
                CUtils::setColor(ColorOfBorder);

                //��λ����
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "��";

                continue;
            }

            if (((i == statePoint.getX() || i == helpPoint.getX()) && (j >= statePoint.getY() && j <= helpPoint.getY()))
                || ((j == statePoint.getY() || j == helpPoint.getY()) && (i >= statePoint.getX() && i <= helpPoint.getX())))
            {
                //ȷ���߿���ɫ
                CUtils::setColor(111);

                //��λ����
                CUtils::gotoXY(scenePoint.getX() - 1 + i, (scenePoint.getY() - 1 + j) * 2);

                cout << "��";

                continue;
            }

        }
    }

    CUtils::setColor();
}

int CWelcomeScene::enterUIScene()
{
    //���ų�����������
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\welcome.wav");

    //��ӡ �߿�
    renderBoder();

    //��ӡ��Ϸѡ��
    rendChoice();

    //Ĭ��ѡ���һ��ѡ��
    int choiceNum = 0;
    renderFlagChoice(choiceNum);


    while (true)
    {
        static DWORD dwPreTime = GetTickCount();  //previous ��ǰ��  -- ��̬�ֲ�����
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

    //��̬���� ���� ��ͼ
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height*sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //����txt�ļ���ʼ����������
    initUISceneArrayOnTextFile("WelcomeScene");

    //��������������
    statePoint = CPosition(3, 5);
    helpPoint = statePoint + CPosition(14, 25);
    describePoint = CPosition(23, 22);
}
