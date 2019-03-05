#pragma once
#include "CScene.h"
#include "CBagDirector.h"

class CBagScene : public CScene
{
public:
    CBagScene();
    ~CBagScene();

    //重要：封装玩家和场景的游戏交互过程
    virtual int enterUIScene();

protected:
    //任务部分------------------------------------------

    //选择任务.
    int choiceTask();

    //打印红色任务字样
    void renderRedTask();

    //打印任务背景边框
    void renderTaskBackground();

    //打印任务信息
    void renderTaskInfo();


    //属性部分------------------------------------------

    //选择属性
    int choiceAttribute();

    //打印红色 属性 字样
    void renderRedAttribute();

    //打印求仙的属性
    void renderQiuXian();

    //打印雅惠的属性
    void renderYaHui();

    //给每人升级
    void levelUpAll();


    //商店部分------------------------------------------

    //打印选择商店
    int choiceShop();

    //进入商店
    int enterShop();

    //打印分界线
    void renderLine();

    //打印红色 商店 字样
    void renderRedShop();

    void buyItem(CPosition _choice);

    //打印选择光标
    void renderSelected(CPosition _pos);

    //擦除物品提示信息
    void eraserItemInfo();

    //打印商店 （1.HP 2.MP 3.长鞭 4.铠甲 ）
    void renderShopStyle();


    //公共部分-----------------------------------

    //打印边框
    void renderBorder();

    //打印帮助信息
    void renderHelpInfo();

    //基类纯虚方法--------------------------------

    //场景打印函数
    virtual void renderSceneUI();
    //从场景数组读取配置
    virtual void initPropsOnSceneArray();

};

