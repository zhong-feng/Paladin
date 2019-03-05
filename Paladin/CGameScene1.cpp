#include "CGameScene1.h"

#include "CMonsterFactory.h"
#include "CFightDirector.h"

#include "CBagScene.h"


int CGameScene1::arrayFog[COLOFGAMESCENE1][ROWOFGAMESCENE1] = { 0 };

bool CGameScene1::devilIsDead = false;


void CGameScene1::freeMonsterList()
{
    auto itr = m_MonsterList.begin();

    while (itr != m_MonsterList.end())
    {
        if (*itr)
        {
            delete (*itr);
            *itr = 0;

            m_MonsterList.pop_front();
            itr = m_MonsterList.begin();
        }
    }
}



void CGameScene1::initPropsOnSceneArray()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //���ô��͵�
            if (ppSceneArray[i][j] == G1_ToScene2)
            {
                toScene2Pos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_ToScene3)
            {
                toScene3Pos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_ToBirth)
            {
                toBirthPos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_Devil)
            {
                if (devilIsDead)
                {
                    ppSceneArray[i][j] = G1_Path;
                    ppSceneArray[i][j+1] = G1_Path;

                    devilPos = CPosition(999, 999);
                }
                else
                {
                    devilPos = CPosition(i, j);
                }

                continue;
            }

            if (ppSceneArray[i][j] == G1_Pig)
            {
                auto pTmpMonster = CMonsterFactory::createMonster((CMonsterID)G1_Pig);
                pTmpMonster->setCurPos(CPosition(i, j));
                pTmpMonster->setPrePos(CPosition(i, j));

                m_MonsterList.push_back(pTmpMonster);

                ppSceneArray[i][j] = G1_Path;
                continue;
            }

            if (ppSceneArray[i][j] == G1_Dog)
            {
                auto pTmpMonster = CMonsterFactory::createMonster((CMonsterID)G1_Dog);
                pTmpMonster->setCurPos(CPosition(i, j));
                pTmpMonster->setPrePos(CPosition(i, j));

                m_MonsterList.push_back(pTmpMonster);

                ppSceneArray[i][j] = G1_Path;
                continue;
            }
        }

    }//end for i


}

bool CGameScene1::breakFog()
{
    //��ұ�����λ��
    if (player.getPos().getX() == 0 || player.getPos().getY() == 0)
    {
        return false;
    }

    for (int i = player.getPos().getX() - canLook; i < player.getPos().getX() + canLook; i++)
    {
        for (int j = player.getPos().getY() - canLook; j < player.getPos().getY() + canLook; j++)
        {
            if (i >= 0 && i < COLOFGAMESCENE1 && j >= 0 && j < ROWOFGAMESCENE1)
            {
                if (CPosition(i, j) - player.getPos() <= canLook)
                {
                    arrayFog[i][j] = 1;
                }
            }
        }
    }

    return true;
}

//�Ƴ����е�����

 void CGameScene1::breakAllFog()
{
    for (int i =0 ; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            arrayFog[i][j] = 1;

        }
    }
}

void CGameScene1::renderSceneUI()
{
    //��������������Ƴ�����
    if (!breakFog())
    {
        return;
    }

    //�������λ��ȷ����ӡ��׼��
    if (!setBasePosByBirthPos())
    {
        return;
    }


    for (size_t i = 0; i < COLOFSCENE; i++)
    {
        for (size_t j = 0; j < ROWOFSCENE; j++)
        {
            //ȷ����ӡλ��
            CUtils::gotoXY(scenePoint.getX() + i, (scenePoint.getY() + j) * 2);

            //������ס ��ӡ�հ�
            if (arrayFog[basePos.getX() + i][basePos.getY() + j] == 0)
            {
                CUtils::setColor();
                cout << "  ";

                continue;
            }

            //����  ʱ�� ˢ�º���״̬
            static DWORD dwPreTime = GetTickCount();
             DWORD dwCurTime = GetTickCount();
             if (dwCurTime - dwPreTime > 1000)
             {
                 dwPreTime = GetTickCount();
                 flagRiver = (!flagRiver);
             }

            //ӳ���ͼ��Ӧ����
            switch (ppSceneArray[basePos.getX() + i][basePos.getY() + j])
            {
            case G1_Dog:
            case G1_Pig:
            case G1_HideBx:
            case G1_Path: { CUtils::setColor(103); cout << "  "; break; }
            case G1_Tree: { CUtils::setColor(42); cout << "��"; break; }
            case G1_River: { CUtils::setColor(23); cout << "  "; break; }
            case G1_Ripple1:
            {
                CUtils::setColor(23);
                if (flagRiver)
                {
                    cout << "  ";
                }
                else
                {
                    cout << "~~";
                }
                break; 
            }
            case G1_Ripple2: 
            { 
                CUtils::setColor(23); 
                if (flagRiver)
                {
                    cout << "~~";
                }
                else
                {
                    cout << "  ";
                }
                break; 
            }
            case G1_Bridge: { CUtils::setColor(103); cout << "��"; break; }
            case G1_ShoalWater: { CUtils::setColor(23); cout << "  "; break; }
            case G1_SmallBox: { CUtils::setColor(111); cout << "��"; break; }
            case G1_BigBox: { CUtils::setColor(108); cout << "��"; break; }

            case G1_DevilT: { CUtils::setColor(192); cout << "��"; break; }
            case G1_Devil: { CUtils::setColor(192); cout << "Ұ"; break; }
            case G1_ToScene2:
            case G1_ToScene3:
            case G1_ToBirth: { CUtils::setColor(140); cout << "��"; break; }
            default: break;
            }

        }
    }

    //����ɫ�Ļ�Ĭ��
    CUtils::setColor();
}

void CGameScene1::renderAllTheMonster()
{
    for (auto element : m_MonsterList)
    {
        //��ȡ���ﵱǰ����
        auto tmpPos = element->getCurPos();

        //ȷ������Ļ��Χ��
        int tmpX = tmpPos.getX() - basePos.getX();
        int tmpY = tmpPos.getY() - basePos.getY();

        if (tmpX > 0 && tmpX < COLOFSCENE && tmpY > 0 && tmpY < ROWOFSCENE)
        {
            //û�б�������ס
            if (arrayFog[tmpPos.getX()][tmpPos.getY()] == 1)
            {
                CUtils::gotoXY(CPosition(tmpX, tmpY) + scenePoint);
                CUtils::setColor(108);
                element->renderMyself();
            }
        }
    }
}

void CGameScene1::moveAllTheMonster()
{
    for (auto element : m_MonsterList)
    {

        element->moveMyself(ppSceneArray);
    }
}

int CGameScene1::enterUIScene()
{
    //���ų�����������
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\gameSence1.wav");

    //��ӡ �߿�
    renderBoder();

    //��ӡ������Ϣ
    renderHelpInfo();

    //��ӡ ����
    renderSceneUI();

    //��ӡ���
    rendScenePlayer();

    while (true)
    {
        //�����û�����
        if (_kbhit())
        {
            //���������ȷ��Ŀ�� ��Ϣ
            CPosition nextPos = player.getPos();
            CDirection nextDirection = DI_NONE;

            char keyCode = _getch();
            switch (keyCode)
            {
            case 'a':
            case 'A': {nextPos = nextPos + DI_LEFT; nextDirection = DI_LEFT; break; }
            case 'w':
            case 'W': {nextPos = nextPos + DI_UP; nextDirection = DI_UP; break; }
            case 'd':
            case 'D': {nextPos = nextPos + DI_RIGHT; nextDirection = DI_RIGHT; break; }
            case 's':
            case 'S': {nextPos = nextPos + DI_DOWN; nextDirection = DI_DOWN; break; }

            case '0': {breakAllFog(); break; }//���� �Ƴ�������

            case 'm':
            case 'M':  //��������ϵͳ
            {
                CBagScene bagSystem;
                bagSystem.enterUIScene();

                //�����Ⱦ
                system("cls");

                //��ӡ �߿�
                renderBoder();

                //��ӡ������Ϣ
                renderHelpInfo();
                break;
            }

            case 27: { return -1; break; }
            default: break;
            }

            int value = getValueOfSceneArrayOnPos(nextPos);

            //�յ� �� ǳˮ ����ֱ������
            if (value == G1_Path || value == G1_ShoalWater || value == G1_Bridge)
            {
                player.setPos(nextPos);
                player.setDirection(nextDirection);
            }

            if (value == G1_ToScene2 || value == G1_ToScene3 || value == G1_ToBirth)
            {
                //��Ч
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                return value;
            }

            // С���� ���ر��� 50% ���ʵ���Ʒ
            if (value == G1_SmallBox || value == G1_HideBx)
            {
                //���˱���� ������ʧ
                setValueOfSceneArrayOnPos(nextPos, G1_Path);

                if ((rand() + rand()*rand()) % 100 > 50)
                {
                    //������Ʒ
                    dropItem();
                }
                else
                {
                    renderMessage("������һ������#���ź���������ʲô��û��");
                }

                //��Ч
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\openBox.wma");

            }

            if (value == G1_BigBox)
            {
                //���˱���� ������ʧ
                setValueOfSceneArrayOnPos(nextPos, G1_Path);

                //������Ʒ
                dropItem();

                //��Ч
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\openBox.wma");
            }

            //���� Ұ�� ս��
            if (nextPos - devilPos < 3)
            {
                if (isWinOfFightWithMonster(MI_Devil))
                {
                    //ʤ�� ɾ��ħ����Ϣ
                    setValueOfSceneArrayOnPos(devilPos, G1_Path);
                    setValueOfSceneArrayOnPos(devilPos + DI_RIGHT, G1_Path);

                    devilIsDead = true;
                    devilPos = CPosition(999, 999);//��Ϊ����������

                }
            }


        } //end if ((_kbhit()))

        //�����ɵ��¼���Ϣ
        eraserMessage();

        //����Ѳ����
        moveAllTheMonster();

        //�� ���� ��ײ
        touchMonster();

        //��ӡ ����
        renderSceneUI();

        //��ӡ����
        renderAllTheMonster();

        //��ӡ���
        rendScenePlayer();
    }

    return -1;
}

CGameScene1::~CGameScene1()
{
    //�ֶ��ͷ�����
    freeMonsterList();
}

CGameScene1::CGameScene1()
{
    toScene2Pos = CPosition(0, 0);
    toScene3Pos = CPosition(0, 0);
    toBirthPos = CPosition(0, 0);

    devilPos = CPosition(0, 0);

    canLook = DISTANCE;

    flagRiver = true;

    //ȷ������
    height = COLOFGAMESCENE1;
    width = ROWOFGAMESCENE1;

    sceneID = SI_GameScene1;
    name = "����";

    //��̬���� ���� ��ͼ
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height * sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //����txt�ļ���ʼ����������
    initUISceneArrayOnTextFile("GameScene1");

    //�ӳ��������ȡ������Ϣ
    initPropsOnSceneArray();
}

void CGameScene1::touchMonster()
{
    for (auto itrMonsyer = m_MonsterList.begin();
        itrMonsyer != m_MonsterList.end(); )
    {
        if ((*itrMonsyer)->getCurPos() - player.getPos() < 3)
        {
            if (isWinOfFightWithMonster((*itrMonsyer)->getMonsterID()))
            {
                // ɾ������
                delete (*itrMonsyer);
                *itrMonsyer = 0;

                m_MonsterList.erase(itrMonsyer);

                //������ʧЧ
                itrMonsyer = m_MonsterList.begin();

                continue;
            }
            else
            {
                return;
            }
 
        }

        itrMonsyer++;
    }
}

bool CGameScene1::isWinOfFightWithMonster(CMonsterID _ID)
{
    //����ս��
    int res = CFightDirector::getInstance()->startFight(_ID);

    system("cls");

    //��ӡ �߿�
    renderBoder();

    //��ӡ������Ϣ
    renderHelpInfo();

    //��ӡ ����
    renderSceneUI();

    //��ӡ����
    renderAllTheMonster();

    //��ӡ���
    rendScenePlayer();

    if (res == 1) //ս��ʤ��
    {
        //�Ӿ��� ����
        if (CYaHui::getInstance()->getIsShow())
        {
            CYaHui::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
            CYaHui::getInstance()->levelUp();
        }

        CQiuDao::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
        CQiuDao::getInstance()->levelUp();

        //��ӡʤ����Ϣ
        renderMessage("��ϲ�㣡ս��ʤ��#��þ��� 100");

        _getch();

        //������Ʒ
        dropItem();

        return true;
    }
    else  //ս��ʧ��
    {
        //ǿ�Ʊ�Ϊһ��Ѫ���ص���ͼ������
        player.setPos(toBirthPos);
        player.setDirection(DI_RIGHT);

        if (CYaHui::getInstance()->getIsShow())
        {
            CYaHui::getInstance()->setCurHP(1);
        }

        CQiuDao::getInstance()->setCurHP(1);

        return false;
    }
}



