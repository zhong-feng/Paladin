#pragma once
#include "CTaskBase.h"


class CTaskDirector :public CSingleton<CTaskDirector>
{
public:
    CTaskDirector();
    ~CTaskDirector();

    list<CTaskBase*>* getTaskList();

protected:
    list<CTaskBase*> taskList;
    GS_SYNTHESIZE(int, countNum, CountNum); // 已接任务 数量
    GS_SYNTHESIZE(int, maxNum, MaxNum);     // 可接任务最大 数量

};

