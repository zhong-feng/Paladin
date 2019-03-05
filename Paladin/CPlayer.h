#pragma once
#include "CPosition.h"
#include "sceneData.h"

class CPlayer
{
public:
    CPlayer();
    ~CPlayer();

    //渲染玩家
    void scenePlayer();

    GS_SYNTHESIZE(CPosition, pos, Pos);  //位置
    GS_SYNTHESIZE(CDirection, direction, Direction); //方向


};

