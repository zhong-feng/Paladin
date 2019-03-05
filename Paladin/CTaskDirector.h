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
    GS_SYNTHESIZE(int, countNum, CountNum); // �ѽ����� ����
    GS_SYNTHESIZE(int, maxNum, MaxNum);     // �ɽ�������� ����

};

