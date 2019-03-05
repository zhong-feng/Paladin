#pragma once

#include "bagData.h"
#include "sceneData.h"
#include "fightData.h"

#define MAXNUMOFTASK 3  //最大可接任务数量

#define MODEUNTAKE     0  //未接受状态
#define MODEUNFINISED  1  //接受 但条件不满足
#define MODEFINISED    2  //条件满足 待提交
#define MODESUBMITED   3  //完成任务 


enum CTaskType
{
    TT_NONE,
    TT_Collect, //收集
    TT_Fight,   //战斗
    TT_FindNPC     //找人
};

enum CTaskID
{
    TI_NONE,    
    TI_CollectApple,
    TI_SikllDog,

};