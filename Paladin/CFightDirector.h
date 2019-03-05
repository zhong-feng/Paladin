#pragma once
#include "CSceneFactory.h"
#include "CMonsterFactory.h"
#include "CQiuDao.h"
#include "CYaHui.h"


class CFightDirector :public CSingleton<CFightDirector>
{
public:
    CFightDirector();
    ~CFightDirector();

    //战斗逻辑
    int startFight(CMonsterID monsterType);

    vector<string>* getFightVec();
protected:
    //胜利后 做杀怪任务
    void doTaskOfKillMonster();

    //打印战斗信息
    void printStateInfo(CPosition _statePos);

    //判断胜负
    int isWin();

    //人物都死完了
    bool isRoleAllDead();

    //怪物都死完了
    bool isMonsterAllDead();

    //创建角色信息
    void createRole();

    //创建怪物信息
    void createMonster(CMonsterID _monsterType);

    //按照 pig 创建怪物信息
    void creatPig();

    //按照 dog 创建怪物信息
    void creatDog();

    //按照 Devil 创建怪物信息
    void creatDevil();

    ////释放 角色 数据
    //void freeRoleDate()
    //{
    //    if (role == 0)
    //    {
    //        return;
    //    }

    //    //释放角色数据
    //    for (int i = 0; i < 2; i++)
    //    {
    //        if (role[i])
    //        {
    //            delete role[i];
    //            role[i] = 0;
    //        }
    //    }

    //    delete[] role;
    //    role = 0;
    //}

    //释放 怪物 数据
    void freeMonsterData();

protected:
    vector<string> fightVec;

    CBasePerson** role;
    CBasePerson** monster;

};

