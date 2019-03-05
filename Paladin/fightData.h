#pragma once

#include "utility.h"
#include "CUtils.h"
#include "CSingleton.h"

#define MAXSKILLNUM 3


//����ID + ����ֵ
enum CMonsterID 
{
    MI_NONE,
    MI_DOG = 50,
    MI_PIG,
    MI_Devil
};

enum CRoleID
{
    RI_NONE,
    RI_QIUDAO = 1,
    RI_YAHUI,
};

enum CRoleInScene
{
    RS_NONE,
    RS_ONE = 1,
    RS_TWO,
};


//����ս��״̬��ö������
enum CFightBuff
{
    FB_NONE,     //0�ĸ���, Ҫ��FB_
    FB_NORMAL,
    FB_ZHONGDU,  //�ж�
    FB_XUANYUN,  //ѣ��

};
