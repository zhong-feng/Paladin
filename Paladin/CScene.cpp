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

    //ȷ������λ��
    scenePoint = CPosition(BASESCENEPOSX, BASESCENEPOSY);
    statePoint = CPosition(BASESCENEPOSX, BASESCENEPOSY + ROWOFSCENE+1);
    describePoint = CPosition(BASESCENEPOSX + COLOFSCENE +1, BASESCENEPOSY);
    helpPoint = CPosition(BASESCENEPOSX+ COLOFSCENE/2, BASESCENEPOSY + ROWOFSCENE + 1);
}

CScene::~CScene()
{
    if (ppSceneArray) //���п�
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
    //ȷ���ļ�·��
    string filePath = ".\\Resource\\Scene\\";
    filePath = filePath + _name + ".txt";

    //���ļ�
    FILE* pFile = 0;
    fopen_s(&pFile, filePath.c_str(), "r");

    //�п�
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

    //�ر��ļ�
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
    //��ӡ������

    //ȷ�� ��ɫ
    CUtils::setColor(12);

    //��λ����
    CUtils::gotoXY(scenePoint.getX() - 3, (scenePoint.getY() +2) * 2);

    cout << name << endl;

    //��ӡ�߿�

    //ȷ���߿���ɫ
    CUtils::setColor(ColorOfBorder);

    //ȷ���߿�λ��
    for (int i = 0; i < MAXCOL; i++)
    {
        for (int j = 0; j < MAXROW; j++)
        {
            if (i == 0 || i == COLOFSCENE + 1 || i == MAXCOL - 1
                || j == 0 || j == MAXROW - 1 || (j == ROWOFSCENE + 1 && i < COLOFSCENE + 1))
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

void CScene::rendScenePlayer()
{
    //������ʱ����� ȷ�����  ���λ��
    CPosition tmpPos = CPosition(0, 0);

    //ȷ�����  ���λ�� x
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

    //ȷ�����  ���λ�� y
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

    //���λ�� + ��Ⱦ���׼�� = ��ҵ�ʵ��λ��
    tmpPos = tmpPos + scenePoint;

    CUtils::gotoXY(tmpPos);

    //������ҵ� ��Ⱦ����
    player.scenePlayer();

    //��ӡ�������
    rendPlayerPos();
}

void CScene::renderHelpInfo()
{
    //�趨��ɫ
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
    cout << "      ������Ϣ";

    CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
    cout << "  �ƶ�: ��   W/w";

    CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
    cout << "        ��   S/s";

    CUtils::gotoXY(helpPoint.getX() + 4, helpPoint.getY() * 2);
    cout << "        ��   A/a";

    CUtils::gotoXY(helpPoint.getX() + 5, helpPoint.getY() * 2);
    cout << "        ��   D/d";

    CUtils::gotoXY(helpPoint.getX() + 7, helpPoint.getY() * 2);
   cout << "  �˵�       B/b";

    CUtils::gotoXY(helpPoint.getX() + 8, helpPoint.getY() * 2);
    cout << "  �˳�       Esc";

    //��ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

void CScene::rendPlayerPos()
{
    CUtils::gotoXY(statePoint.getX() + 1, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "      ��ǰ����";

    CUtils::gotoXY(statePoint.getX() + 3, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "    ��     ";
    CUtils::setColor(12);
    cout << player.getPos().getX();



    CUtils::gotoXY(statePoint.getX() + 4, statePoint.getY() * 2);
    CUtils::setColor(10);
    cout << "    ��     ";
    CUtils::setColor(12);
    cout << player.getPos().getY();

    CUtils::setColor();
}

bool CScene::setBasePosByBirthPos()
{
    //��ұ�����λ��
    if (player.getPos().getX() == 0 || player.getPos().getY() == 0)
    {
        return false;
    }

    //ȷ����׼�� x ����
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

    //ȷ����׼�� y ����
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
    //����֮ǰ����Ⱦ
    dwPreMessage = 0;
    eraserMessage();

    //��¼��Ϣʱ��
    dwPreMessage = GetTickCount();
    //ȷ����ӡ��ɫ
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


    //�����Ϣ���� ��ʱ����Ϊ���ֵ������Ϊ�������ٴ������
    dwPreMessage = GetTickCount() * 10;
}

void CScene::dropItem()
{
    //��ý�Ǯ
    int tmpMoney = 1000;

    //�����Ʒ
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

    //����Ʒ���뱳��
    CBagDirector::getInstance()->setMoney(CBagDirector::getInstance()->getMoney() + tmpMoney);
    CBagDirector::getInstance()->getBag()->addItem(tmpItem);

    char buffer[10] = { 0 };
    _itoa_s(tmpMoney, buffer, 10);
    string tmpStr = "��ϲ���ã�#��Ǯ  ";
    tmpStr = tmpStr + buffer + "#��Ʒ  ";

    auto pTmpItem = CItemFactory::createItem((CItemID)tmpItem);

    tmpStr = tmpStr + pTmpItem->name;

    delete pTmpItem;
    pTmpItem = 0;

    renderMessage(tmpStr.c_str());
}
