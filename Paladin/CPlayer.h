#pragma once
#include "CPosition.h"
#include "sceneData.h"

class CPlayer
{
public:
    CPlayer();
    ~CPlayer();

    //��Ⱦ���
    void scenePlayer();

    GS_SYNTHESIZE(CPosition, pos, Pos);  //λ��
    GS_SYNTHESIZE(CDirection, direction, Direction); //����


};

