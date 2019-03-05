#pragma once
#include "utility.h"
#include "CUtils.h"
#include "CSingleton.h"

//背包大小
#define COLOFBAG 16
#define ROLOFBAG 10

#define BAGPROMPTPOSX 11
#define BAGPROMPTPOSY 11

#define COLOFMESSAGE 7
#define ROWOFMESSAGE 9

enum CItemID //物品ID
{
    ID_None,
    ID_HP = 1,        //HP药水 药品
    ID_MP,            //
                      
    ID_Sword = 10,    //剑  武器
    ID_Whips,         //鞭子
                      
    ID_Ioricae = 20,    //铠甲  衣服
    ID_Sackcloth,       //布衣
                      
    ID_Apple=30,         //苹果  任务物品

};


enum CItemType
{
    IT_None,     //零 值
    IT_Drug,     //药品
    IT_Weapon,   //武器
    IT_Garment,  //衣服
    IT_Task,     //任务物品
};
