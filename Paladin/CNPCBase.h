#pragma once
#include "taskData.h"

class CNPCBase
{
public:
    CNPCBase()
    {
        NPCID = SN_NONE;
        name = "";
        taskID = TI_NONE;
    }
    ~CNPCBase()
    {

    }

    


protected:
    GS_SYNTHESIZE(CSceneNPC, NPCID, NPCID); // NPC ID
    GS_SYNTHESIZE(string, name, Name);      // ����
    GS_SYNTHESIZE(CTaskID, taskID, TaskID); //��������

};

