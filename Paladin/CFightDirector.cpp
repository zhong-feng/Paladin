#include "CFightDirector.h"
#include "CTaskDirector.h"

CFightDirector::CFightDirector()
{
    monster = nullptr;

    role = new CBasePerson*[2];
    memset(role, 0, 2 * sizeof(CBasePerson*));

    //确认角色属性
    createRole();
}

CFightDirector::~CFightDirector()
{
    ////释放 角色 数据
    //freeRoleDate();

    //释放 怪物 数据
    freeMonsterData();
}

//战斗逻辑

int CFightDirector::startFight(CMonsterID _monsterID)
{

    //播放场景背景音乐
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\fight.wav");

    //给怪物分配内存空间
    monster = new CBasePerson*[4];
    memset(monster, 0, 4 * sizeof(CBasePerson*));

    //根据碰到的怪物创建相应的怪物
    createMonster(_monsterID);

    //渲染地图
    CScene* tmpScene = CSceneFactory::createScene(CI_FIGHTSCENE);
    tmpScene->enterUIScene();

    //获取说明信息打印坐标
    auto statePos = tmpScene->getStatePoint();
    statePos = statePos + CPosition(3, 1);

    //释放临时场景
    delete tmpScene;
    tmpScene = 0;

    //渲染角色信息
    for (int i = 0; i < 2; i++)
    {
        if (role[i]->getIsShow())
        {
            role[i]->printInfo();
            role[i]->printFace();
        }

    }

    //渲染怪物信息
    for (int i = 0; i < 4; i++)
    {
        monster[i]->printInfo();
        monster[i]->printFace();

    }

    //循环 出手
    while (true)
    {
        // 玩家先手
        for (int i = 0; i < 2; i++)
        {
            // 出手前先 判断是否结束
            if (int res = isWin())
            {
                //释放怪物数据
                freeMonsterData();

                return res;
            }

            //角色不在队伍 跳过
            if (role[i]->getIsShow() == false)
            {
                continue;
            }

            //已死亡，直接跳过
            if (role[i]->getCurHP() == 0)
            {
                continue;
            }

            // 没有 眩晕 
            if (role[i]->getMapBuff()->count(FB_XUANYUN) == 0)
            {
                //出手攻击
                role[i]->fight(role, monster);

                //更新战斗信息
                printStateInfo(statePos);
            }

            //如果中毒  扣血
            if (role[i]->getMapBuff()->count(FB_ZHONGDU) == 1)
            {
                role[i]->setCurHP(role[i]->getCurHP() - 50);
            }

            //所中状态时间  -1
            role[i]->subFightBuffTime();

            //打印当前状态
            role[i]->printInfo();

        }

        //怪物后手
        for (int i = 0; i < 4; i++)
        {
            // 出手前先 判断是否结束
            if (int res = isWin())
            {
                //释放怪物数据
                freeMonsterData();

                return res;
            }

            //已死亡，直接跳过
            if (monster[i]->getCurHP() == 0)
            {
                continue;
            }

            // 没有 眩晕 
            if (monster[i]->getMapBuff()->count(FB_XUANYUN) == 0)
            {
                //怪物攻击
                monster[i]->fight(role, monster);

                //更新战斗信息
                printStateInfo(statePos);
            }

            //如果中毒  扣血
            if (monster[i]->getMapBuff()->count(FB_ZHONGDU) == 1)
            {
                monster[i]->setCurHP(monster[i]->getCurHP() - 50);
            }

            //所中状态时间  -1
            monster[i]->subFightBuffTime();

            //打印当前状态
            monster[i]->printInfo();

            Sleep(700);
        }

    }
}

vector<string>* CFightDirector::getFightVec()
{
    return &fightVec;
}

//打印战斗信息

void CFightDirector::printStateInfo(CPosition _statePos)
{
    //创建迭代器
    auto itr = fightVec.begin();

    //打印 容器中最上面的10条信息
    for (int i = 0; i < 10; i++)
    {
        if (itr == fightVec.end())
        {
            return;
        }

        //先清空
        CUtils::gotoXY(_statePos);
        cout << "                              " << endl;

        //在打印
        CUtils::gotoXY(_statePos);
        cout << *itr << endl;

        itr++;
        _statePos = _statePos + DI_DOWN;
    }
}

//判断胜负

int CFightDirector::isWin()
{
    int res = 0;



    if (isRoleAllDead())
    {
        res = -1;
    }
    else if (isMonsterAllDead())
    {
        //音效
        CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\win.wav");

        res = 1;
    }

    //清空 战斗信息
    if (res != 0)
    {
        //清空人物 战斗状态
        for (int i = 0; i < 2; i++)
        {
            if (role[0]->getIsShow())
            {
                role[0]->getMapBuff()->clear();
            }
        }

        //清空提示信息
        fightVec.clear();
    }

    return res;
}

//人物都死完了

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

//怪物都死完了

bool CFightDirector::isMonsterAllDead()
{
    for (int i = 0; i < 4; i++)
    {
        if (monster[i]->getCurHP() > 0)
        {
            return false;
        }

    }

    //胜利后 做杀怪任务
     doTaskOfKillMonster();

    ////统计 杀怪 任务 
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

//创建角色信息

void CFightDirector::createRole()
{
    role[0] = CQiuDao::getInstance();
    role[1] = CYaHui::getInstance();
}

//创建怪物信息

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

//按照 pig 创建怪物信息

void CFightDirector::creatPig()
{
    for (int i = 0; i < 4; i++)
    {
        monster[i] = CMonsterFactory::createMonster(MI_PIG);
        ((CMonster**)monster)[i]->setOrderNum(CMonster::countNum);
        CMonster::countNum++;
    }
}

//按照 dog 创建怪物信息

void CFightDirector::creatDog()
{
    for (int i = 0; i < 4; i++)
    {
        monster[i] = CMonsterFactory::createMonster(MI_DOG);
        ((CMonster**)monster)[i]->setOrderNum(CMonster::countNum);
        CMonster::countNum++;
    }
}

//按照 Devil 创建怪物信息

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

//释放 怪物 数据

void CFightDirector::freeMonsterData()
{
    if (monster == 0)
    {
        return;
    }

    //释放怪物数据
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
    //循环遍历任务 链表 
    auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();
    for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((*itr)->monsterID == ((CMonster**)monster)[i]->getMonsterID())
            {
                //杀怪数 +1  
                (*itr)->monsterCount++;

                //杀怪数达到最大值 改变任务状态
                if ((*itr)->monsterCount >= (*itr)->itemMax)
                {
                    (*itr)->taskMode = MODEFINISED;
                }

            }

        }  //end for monster
    }
}
