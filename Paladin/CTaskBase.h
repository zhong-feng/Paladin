#pragma once
#include "taskData.h"

class CTaskBase
{
public:
    CTaskBase(CTaskID _id);
    ~CTaskBase();

    int enterTask(CSceneNPC speakNPC, CPosition _pos);

protected:
    //外部文件配置任务
    void initTaskPropOnXml(CTaskID _id);

    //打印 接任务选择区域
    void renderBackgroundOfChoice(CPosition _pos)
    {
        auto tmpPos = _pos;

        for (int i = 0; i < 4; i++)
        {
            CUtils::gotoXY(tmpPos);
            cout << "           ";
            tmpPos = tmpPos + DI_DOWN;
        }
        
        tmpPos = _pos + CPosition(1, 1);
        CUtils::gotoXY(tmpPos);
        cout << "→ 接受";

        CUtils::gotoXY(tmpPos+DI_DOWN);
        cout << "   拒绝";
    }



    //任务没接受
    void enterTaskModde0(CSceneNPC speakNPC, CPosition _pos);

    //接受任务 但是没完成
    void enterTaskModde1(CSceneNPC speakNPC, CPosition _pos);

    //完成任务 但是没提交
    void enterTaskModde2(CSceneNPC speakNPC, CPosition _pos);

    //完成任务给奖励
    void giveReward();


    //打印提示消息
    void renderMessage(const char* str, CPosition _pos);

    //擦除消息提示框
    void eraserMessage(CPosition _pos);
public:
    CTaskID ID;          //任务 ID
    CTaskType taskType;  //任务类型
    string name;         //任务名称

    CSceneNPC provideNpcID; //接任务 NPC ID
    CSceneNPC regainNpcID;  //还任务 NPC ID

    string info;      //发布任务信息
    string receipt;   //确认接受任务信息

    string accept;    //接受任务
    string refuse;    //拒绝任务

    string unfiniseded;   //任务 未完成
    string finished;      //任务 已完成

    CItemID itemID;    //任务物品 ID
    int itemMax;       //需要的 数量
    int itemCount;     //已有的 数量

    CMonsterID monsterID;     //任务怪物 ID
    int monsterMax;           //需要的 数量
    int monsterCount;         //已有的 数量

    int giveMoney;     //奖励金币
    CItemID giveItem;  //奖励物品

    int taskMode;      //当前任务状态

};

