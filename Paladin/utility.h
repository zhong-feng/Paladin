#pragma once
//����ͷ�ļ�
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

//���εĺ�
#define GS_SYNTHESIZE(varType, varName, funName) \
protected: varType varName; \
public: virtual varType get##funName(void) const { return varName; } \
public: virtual void set##funName(varType var){ varName = var; }

//---TinyXml������----
#include ".//TinyXml//tinyxml.h"


//---------------
//��ý�岥��API
#include <mmsystem.h>   //MultiMedia
#pragma comment(lib,"winmm.lib")
//-------------------
