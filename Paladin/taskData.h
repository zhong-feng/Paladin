#pragma once

#include "bagData.h"
#include "sceneData.h"
#include "fightData.h"

#define MAXNUMOFTASK 3  //���ɽ���������

#define MODEUNTAKE     0  //δ����״̬
#define MODEUNFINISED  1  //���� ������������
#define MODEFINISED    2  //�������� ���ύ
#define MODESUBMITED   3  //������� 


enum CTaskType
{
    TT_NONE,
    TT_Collect, //�ռ�
    TT_Fight,   //ս��
    TT_FindNPC     //����
};

enum CTaskID
{
    TI_NONE,    
    TI_CollectApple,
    TI_SikllDog,

};