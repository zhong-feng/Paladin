#pragma once
#include "CPlayer.h"


class CScene
{
public:
    CScene();
    virtual ~CScene();

    //重要：封装玩家和场景的游戏交互过程
    virtual int enterUIScene() = 0;


    //获取和更新 场景数组的值
    void setValueOfSceneArrayOnPos(CPosition position, int value);
    int getValueOfSceneArrayOnPos(CPosition position);

protected:
    //根据txt文件初始化场景数组
    void initUISceneArrayOnTextFile(string _name);

    //从场景数组读取配置
    virtual void initPropsOnSceneArray() = 0;

    //场景打印函数
    virtual void renderSceneUI() = 0;

    //根据玩家位置确定打印基准点
    bool setBasePosByBirthPos();

    //打印边框
     void renderBoder();

    //打印帮助信息
    void renderHelpInfo();

    //打印 触发的 事件
    void renderMessage(const char* str);

    //擦除 事件信息
    void eraserMessage();

    //打印玩家坐标位置
    void rendPlayerPos();

    //渲染玩家信息
    void rendScenePlayer();

    //掉落物品
    void dropItem();

protected:
    //场景 ID
    GS_SYNTHESIZE(CSceneID, sceneID, SceneID);

    GS_SYNTHESIZE(string, name, Name);

    //场景长和宽
    GS_SYNTHESIZE(int, height, Height);  //行
    GS_SYNTHESIZE(int, width, Width);    //列

    //场景UI对应逻辑数组
    int** ppSceneArray;  //动态创建 二维整体数组

    //滚动打印 基准点
    GS_SYNTHESIZE(CPosition, basePos, BasePos);

    //场景中特殊点和文本输出点
    GS_SYNTHESIZE(CPosition, scenePoint, ScenePoint);
    GS_SYNTHESIZE(CPosition, statePoint, StatePoint);
    GS_SYNTHESIZE(CPosition, describePoint, DescribePoint);
    GS_SYNTHESIZE(CPosition, helpPoint, HelpPoint);

    //主角信息
    GS_SYNTHESIZE(CPlayer, player, Player);

    //消息出现的时间
    DWORD dwPreMessage;
   

};

