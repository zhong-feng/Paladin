#pragma once
//公有头文件
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

//带参的宏
#define GS_SYNTHESIZE(varType, varName, funName) \
protected: varType varName; \
public: virtual varType get##funName(void) const { return varName; } \
public: virtual void set##funName(varType var){ varName = var; }

//---TinyXml解析库----
#include ".//TinyXml//tinyxml.h"


//---------------
//多媒体播放API
#include <mmsystem.h>   //MultiMedia
#pragma comment(lib,"winmm.lib")
//-------------------
