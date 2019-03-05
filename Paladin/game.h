#pragma once
//游戏头文件
#include "utility.h"
#include "CUtils.h"
#include "CSingleton.h"


//颜色相关
#define ColorOfPlayer 12
#define ColorOfBorder 243
#define COLEROFHELP 10


enum CDirection  //方向枚举类型
{
    DI_NONE,
    DI_UP,  //上
    DI_DOWN,
    DI_RIGHT,
    DI_LEFT
};