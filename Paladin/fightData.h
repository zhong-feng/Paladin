#pragma once

#include "utility.h"
#include "CUtils.h"
#include "CSingleton.h"

#define MAXSKILLNUM 3


//怪物ID + 配置值
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


//定义战斗状态的枚举类型
enum CFightBuff
{
    FB_NONE,     //0的概念, 要加FB_
    FB_NORMAL,
    FB_ZHONGDU,  //中毒
    FB_XUANYUN,  //眩晕

};
