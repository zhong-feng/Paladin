#pragma once

#include "CPosition.h"

//操作界面的高和宽
#define MAXCOL 29
#define MAXROW 33

//场景的高宽
#define COLOFSCENE 20
#define ROWOFSCENE 20

//场景的起始点坐标
#define BASESCENEPOSX 4
#define BASESCENEPOSY 7

//战斗场景 
#define FIGHTSTATEPOINTWIDE 18
#define FIGHTDESRIBEPOINTWIDE 7


#define COLOFBIRTHSCENE 42   //新手村场景长宽
#define ROWOFBIRTHSCENE 46

#define COLOFGAMESCENE1 38     //场景1 场景长宽
#define ROWOFGAMESCENE1 41

//视野范围
#define DISTANCE 5

#define COLOFGAMESCENE2 20     //场景2 场景长宽
#define ROWOFGAMESCENE2 20

//安却区域
#define SAFETYLENGTH 3

#define COLOFGAMESCENE3 20     //场景3 场景长宽
#define ROWOFGAMESCENE3 20


enum CSceneID //场景名
{
    SI_None,
    SI_WelcomeScene,    //欢迎场景
    SI_BirthScene,      //新手村场景
    SI_GameScene1,      //关卡1
    SI_GameScene2,      //关卡2
    SI_GameScene3,      //关卡3
};

enum CSceneTransfer     //传送点
{
    CI_NONE,

    CI_BirthTOScene1 = 100,  //出生地 传送 到 郊外1  100

    CI_Scene1TOScene2,    //郊外1 传送 到 地洞一层2   101
    CI_Scene1TOScene3,    //郊外1 传送 到 地洞二层3   102
    CI_Scene1TOBirth,     //郊外1 传送 到 出生地      103

    CI_Scene2TOScene3,    //地洞一层2 传送 到 地洞二层3   104
    CI_Scene2TOScene1,    //地洞一层2 传送 到 郊外1       105

    CI_Scene3TOScene2,    //地洞二层3 传送 到 地洞一层2   106
    CI_Scene3TOScene1,    //地洞二层3 传送 到 郊外1       107

    CI_FIGHTSCENE = 140,
    CI_WELCOME,


};

enum CSceneNPC //NPC
{
    SN_NONE,
    SN_YAHUI = 150,   //出生地 雅惠
    SN_SHOP,          //出生地 商店
    SN_JIA,           //出生地 甲  152
    SN_YI,            //出生地 乙  153
};

enum CBirthsceneInfo
{
    BI_PATH = 0,  //空地
    BI_BORDER,    //边框
    BI_TREE,      //树  
    BI_FENCE,     //栅栏
    BI_WINDOW,    //窗户
    BI_WALL,      //墙
    BI_PASS,      //跳过
    BI_ROOF1,     //屋顶1
    BI_ROOF2,     //    2
    BI_ROOF3,     //    3
    BI_ROOF4,     //    4

    BI_BED,       //床
    BI_SARK,      //柜子

    BI_YAHUIPASS = 25,
    BI_SHOPPASS,

    BI_BIRTH = 30,  //出生点

    BI_TOSCENE1 = 100,   //传送点

    BI_YAHUI = 150,   //NPC
    BI_SHOP,
    BI_JIA,
    BI_YI,
};


enum CGameScene1Info
{
    G1_Path = 0,       //  空地

    G1_Tree = 2,       //树
    G1_River,        //河
    G1_Ripple1,      //水波1
    G1_Ripple2,      //t
    G1_Bridge,       //桥
    G1_ShoalWater,   // 浅水

    G1_SmallBox = 10,  //小宝箱
    G1_BigBox,       //大宝箱
    G1_HideBx,       //隐藏的宝箱

    G1_DevilT = 30,    //魔鬼占位

    G1_Dog = 50,     //狗
    G1_Pig,          //猪
    G1_Devil ,       //魔鬼
  
    

    G1_ToScene2 = 101, //传送 到 场景2
    G1_ToScene3,     //传送 到 场景3 
    G1_ToBirth,      //传送 到 出生地
};


enum CGameScene2Info
{
    G2_Path = 0,       //空地
    G2_Border,         //边框

    G2_SmallBox = 10,  //  小宝箱
    G2_HideBx = 12,    //隐藏的宝箱

    G2_Dog = 50,     //狗
    G2_Pig,          //猪

    G2_ToScene3 = 104,     //传送 到 场景3 
    G2_ToScene1 ,          //传送 到 场景1

};


enum CGameScene3Info
{
    G3_Path = 0,       //空地
    G3_Border,         //边框

    G3_SmallBox = 10,  //  小宝箱
    G3_HideBx = 12,    //隐藏的宝箱

    G3_Dog = 50,     //狗
    G3_Pig,          //猪

    G3_ToScene2 = 106, //传送 到 场景2
    G3_ToScene1,       //传送 到 场景1 
};

