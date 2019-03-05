#pragma once
#include "CBag.h"

#include "CSelectedCursor.h"

class CBagDirector :public CSingleton<CBagDirector>
{
public:
    CBagDirector();
    ~CBagDirector();


    //进入背包系统
    int enterBagSystem();

    //打印背包信息
    void renderBag();

    int getMoney();
    void setMoney(int _num);

    CBag* getBag();

protected:
    //选择操作光标单元格
    void enterSelectedCurosor();

    //丢弃物品
    void castOffItem();

    //出售物品
    void saleItem();
    

    //可选列表（返回可选最大值）
    int renderCanChoiceList();

    //使用光标选择的物品
    void useTheSelectedCursorItem();

    //装备 武器
    void useWeapon(CItem* _weapon,CRole* _role);

    //装备 防具
    void useGarment(CItem* _garment, CRole* _role);
    
    //提示信息 界面渲染
    void renderMessageUIScence();

    //擦除 提示信息 界面渲染
    void eraserMessageUIScence();

    //渲染 选择 对象画面
    int renderChoiceUIScene();

    //擦除选择画面
    void eraserChoiceUIScene();

    //随机添加物品 1-3件
    void randomAddItem();

    //移动光标
    void moveSelectedCursor(CDirection _direction);

    //背包系统的初始化
    void onInit();

    //擦除旧的物品提示信息
    void eraserItemInfo();

    //打印帮助信息
    void renderHelpInfo();

    //打印物品提示信息
    void displaySelectedItemInfo();

    //背包系统的渲染更新--------------
    void renderBagSystemUI();

protected:
    //背包对象： 背包本身的逻辑 + 背包的图案
    CBag * m_pBag;

    //打印背包画面的起点
    CPosition pointOfBagStartRender;

    //打印物品信息的起点
    CPosition pointOfShowItemInfo;

    //打印提示信息的起点
    CPosition pointOfShowHelpInfo;

    //【选择光标】
    CSelectedCursor selectedCursor;

    //金钱
    static int money;
};

