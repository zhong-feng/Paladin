#pragma once
#include "CScene.h"


class CBirthScene : public CScene
{
public:
    CBirthScene();

    ~CBirthScene();

    //重写写出生场景的 交互
    int enterUIScene();


protected:
    //场景打印函数
    void renderSceneUI()override;

    //从场景数组读取 配置 信息
    void initPropsOnSceneArray() override;

    //开场剧情
    void renderStory();

    //开场初始任务
    void renderMessage1();

    //触发 雅惠 的任务
    void renderFindYaHui();

    //NPC 甲 的任务（找苹果 / 可重复接取）
    void renderFindJia();

    //NPC 乙 的任务 （杀狗）
    void renderFindYi();

public:
    //确认是否第一次出现
    static bool isFirstToBirthscene;

    static int countKillDog;

private:
    GS_SYNTHESIZE(CPosition, birthPos, BirthPos);
    GS_SYNTHESIZE(CPosition, toScene1pPos, ToScene1pPos);

    GS_SYNTHESIZE(CPosition, NPCYaHuiPos, NPCYaHuiPos);
    GS_SYNTHESIZE(CPosition, NPCShopPos, NPCShopPos);

    GS_SYNTHESIZE(CPosition, NPCJiaPos, NPCJiaPos);
    GS_SYNTHESIZE(CPosition, NPCYiPos, NPCYiPos);

};

