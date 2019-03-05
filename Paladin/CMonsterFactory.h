#pragma once
#include "CDog.h"
#include "CDevil.h"
#include "CPig.h"

class CMonsterFactory
{
public:
    static CMonster* createMonster(CMonsterID _monsterID);

};

