#include "CTaskDirector.h"




CTaskDirector::~CTaskDirector()
{
    for (auto element : taskList)
    {
        if (element != nullptr)
        {
            delete element;
            element = 0;
        }
    }

    taskList.clear();
}

CTaskDirector::CTaskDirector()
{
    countNum = 0;
    maxNum = MAXNUMOFTASK;
}

list<CTaskBase*>* CTaskDirector::getTaskList()
{
    return &taskList;
}
