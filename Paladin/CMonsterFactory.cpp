#include "CMonsterFactory.h"


CMonster* CMonsterFactory::createMonster(CMonsterID _monsterID)
{
    CMonster* tmpMonster = nullptr;

    switch (_monsterID)
    {
    case MI_DOG:{tmpMonster = new CDog(); break; }
    case MI_PIG:{tmpMonster = new CPig(); break; }
    case MI_Devil:{tmpMonster = new CDevil(); break; }
    default: break;
    }

    return tmpMonster;
}
