#pragma once
#include "CScene.h"
class CFightScene :
    public CScene
{
public:
    CFightScene();
    ~CFightScene();

    //打印边框
    void renderBoder();

    //打印帮助信息
    void renderHelpInfo();
    
    //重写基类纯虚函数
    void initPropsOnSceneArray();//从场景数组读取配置
    void renderSceneUI();//场景打印函数
    int enterUIScene();//重要：封装玩家和场景的游戏交互过程

public:
    list<string> fightInfoList;

};

