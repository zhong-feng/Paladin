#include "CFightDirector.h"
#include "CTaskDirector.h"

CFightDirector::CFightDirector()
{
    monster = nullptr;

    role = new CBasePerson*[2];
    memset(role, 0, 2 * sizeof(CBasePerson*));

    //ȷ�Ͻ�ɫ����
    createRole();
}

CFightDirector::~CFightDirector()
{
    ////�ͷ� ��ɫ ����
    //freeRoleDate();

    //�ͷ� ���� ����
    freeMonsterData();
}

//ս���߼�

int CFightDirector::startFight(CMonsterID _monsterID)
{

    //���ų�����������
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\fight.wav");

    //����������ڴ�ռ�
    monster = new CBasePerson*[4];
    memset(monster, 0, 4 * sizeof(CBasePerson*));

    //���������Ĺ��ﴴ����Ӧ�Ĺ���
    createMonster(_monsterID);

    //��Ⱦ��ͼ
    CScene* tmpScene = CSceneFactory::createScene(CI_FIGHTSCENE);
    tmpScene->enterUIScene();

    //��ȡ˵����Ϣ��ӡ����
    auto statePos = tmpScene->getStatePoint();
    statePos = statePos + CPosition(3, 1);

    //�ͷ���ʱ����
    delete tmpScene;
    tmpScene = 0;

    //��Ⱦ��ɫ��Ϣ
    for (int i = 0; i < 2; i++)
    {
        if (role[i]->getIsShow())
        {
            role[i]->printInfo();
            role[i]->printFace();
        }

    }

    //��Ⱦ������Ϣ
    for (int i = 0; i < 4; i++)
    {
        monster[i]->printInfo();
        monster[i]->printFace();

    }

    //ѭ�� ����
    while (true)
    {
        // �������
        for (int i = 0; i < 2; i++)
        {
            // ����ǰ�� �ж��Ƿ����
            if (int res = isWin())
            {
                //�ͷŹ�������
                freeMonsterData();

                return res;
            }

            //��ɫ���ڶ��� ����
            if (role[i]->getIsShow() == false)
            {
                continue;
            }

            //��������ֱ������
            if (role[i]->getCurHP() == 0)
            {
                continue;
            }

            // û�� ѣ�� 
            if (role[i]->getMapBuff()->count(FB_XUANYUN) == 0)
            {
                //���ֹ���
                role[i]->fight(role, monster);

                //����ս����Ϣ
                printStateInfo(statePos);
            }

            //����ж�  ��Ѫ
            if (role[i]->getMapBuff()->count(FB_ZHONGDU) == 1)
            {
                role[i]->setCurHP(role[i]->getCurHP() - 50);
            }

            //����״̬ʱ��  -1
            role[i]->subFightBuffTime();

            //��ӡ��ǰ״̬
            role[i]->printInfo();

        }

        //�������
        for (int i = 0; i < 4; i++)
        {
            // ����ǰ�� �ж��Ƿ����
            if (int res = isWin())
            {
                //�ͷŹ�������
                freeMonsterData();

                return res;
            }

            //��������ֱ������
            if (monster[i]->getCurHP() == 0)
            {
                continue;
            }

            // û�� ѣ�� 
            if (monster[i]->getMapBuff()->count(FB_XUANYUN) == 0)
            {
                //���﹥��
                monster[i]->fight(role, monster);

                //����ս����Ϣ
                printStateInfo(statePos);
            }

            //����ж�  ��Ѫ
            if (monster[i]->getMapBuff()->count(FB_ZHONGDU) == 1)
            {
                monster[i]->setCurHP(monster[i]->getCurHP() - 50);
            }

            //����״̬ʱ��  -1
            monster[i]->subFightBuffTime();

            //��ӡ��ǰ״̬
            monster[i]->printInfo();

            Sleep(700);
        }

    }
}

vector<string>* CFightDirector::getFightVec()
{
    return &fightVec;
}

//��ӡս����Ϣ

void CFightDirector::printStateInfo(CPosition _statePos)
{
    //����������
    auto itr = fightVec.begin();

    //��ӡ �������������10����Ϣ
    for (int i = 0; i < 10; i++)
    {
        if (itr == fightVec.end())
        {
            return;
        }

        //�����
        CUtils::gotoXY(_statePos);
        cout << "                              " << endl;

        //�ڴ�ӡ
        CUtils::gotoXY(_statePos);
        cout << *itr << endl;

        itr++;
        _statePos = _statePos + DI_DOWN;
    }
}

//�ж�ʤ��

int CFightDirector::isWin()
{
    int res = 0;



    if (isRoleAllDead())
    {
        res = -1;
    }
    else if (isMonsterAllDead())
    {
        //��Ч
        CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\win.wav");

        res = 1;
    }

    //��� ս����Ϣ
    if (res != 0)
    {
        //������� ս��״̬
        for (int i = 0; i < 2; i++)
        {
            if (role[0]->getIsShow())
            {
                role[0]->getMapBuff()->clear();
            }
        }

        //�����ʾ��Ϣ
        fightVec.clear();
    }

    return res;
}

//���ﶼ������

bool CFightDirector::isRoleAllDead()
{
    for (int i = 0; i < 2; i++)
    {
        if (role[i]->getIsShow() && role[i]->getCurHP() > 0)
        {
            return false;
        }

    }

    return true;
}

//���ﶼ������

bool CFightDirector::isMonsterAllDead()
{
    for (int i = 0; i < 4; i++)
    {
        if (monster[i]->getCurHP() > 0)
        {
            return false;
        }

    }

    //ʤ���� ��ɱ������
     doTaskOfKillMonster();

    ////ͳ�� ɱ�� ���� 
    //for (int i = 0; i < 4; i++)
    //{
    //    auto tmpMonsterID = ((CMonster**)monster)[i]->getMonsterID();

    //    if (CBirthScene::countKillDog >= 0 && CBirthScene::countKillDog<20)
    //    {
    //        if (tmpMonsterID == MI_DOG)
    //        {
    //            CBirthScene::countKillDog++;
    //        }
    //    }

    //}

    return true;
}

//������ɫ��Ϣ

void CFightDirector::createRole()
{
    role[0] = CQiuDao::getInstance();
    role[1] = CYaHui::getInstance();
}

//����������Ϣ

void CFightDirector::createMonster(CMonsterID _monsterType)
{
    switch (_monsterType)
    {
    case MI_DOG: { creatDog(); break; }
    case MI_PIG: {  creatPig();  break; }
    case MI_Devil: { creatDevil(); break; }
    default: break;
    }
}

//���� pig ����������Ϣ

void CFightDirector::creatPig()
{
    for (int i = 0; i < 4; i++)
    {
        monster[i] = CMonsterFactory::createMonster(MI_PIG);
        ((CMonster**)monster)[i]->setOrderNum(CMonster::countNum);
        CMonster::countNum++;
    }
}

//���� dog ����������Ϣ

void CFightDirector::creatDog()
{
    for (int i = 0; i < 4; i++)
    {
        monster[i] = CMonsterFactory::createMonster(MI_DOG);
        ((CMonster**)monster)[i]->setOrderNum(CMonster::countNum);
        CMonster::countNum++;
    }
}

//���� Devil ����������Ϣ

void CFightDirector::creatDevil()
{
    monster[0] = CMonsterFactory::createMonster(MI_Devil);
    ((CMonster**)monster)[0]->setOrderNum(CMonster::countNum);
    CMonster::countNum++;


    for (int i = 1; i < 4; i++)
    {
        if ((rand() + rand()*rand()) % 100 > 50)
        {
            monster[i] = monster[i] = CMonsterFactory::createMonster(MI_PIG);
        }
        else
        {
            monster[i] = CMonsterFactory::createMonster(MI_DOG);
        }

        ((CMonster**)monster)[i]->setOrderNum(CMonster::countNum);
        CMonster::countNum++;

    }
}

//�ͷ� ���� ����

void CFightDirector::freeMonsterData()
{
    if (monster == 0)
    {
        return;
    }

    //�ͷŹ�������
    for (int i = 0; i < CMonster::countNum; i++)
    {
        if (monster[i])
        {
            delete monster[i];
            monster[i] = 0;
        }
    }

    delete monster;
    monster = 0;

    CMonster::countNum = 0;
}

void CFightDirector::doTaskOfKillMonster()
{
    //ѭ���������� ���� 
    auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();
    for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((*itr)->monsterID == ((CMonster**)monster)[i]->getMonsterID())
            {
                //ɱ���� +1  
                (*itr)->monsterCount++;

                //ɱ�����ﵽ���ֵ �ı�����״̬
                if ((*itr)->monsterCount >= (*itr)->itemMax)
                {
                    (*itr)->taskMode = MODEFINISED;
                }

            }

        }  //end for monster
    }
}
