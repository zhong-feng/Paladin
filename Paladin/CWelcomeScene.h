#pragma once
#include "CScene.h"
class CWelcomeScene :  public CScene
{
public:
    CWelcomeScene();
    ~CWelcomeScene();

    // 通过 CScene 继承
    virtual int enterUIScene() override;

protected:
    //打印边框
    void renderBoder();

    //打印滚动 特效
    void renderRoler();

    //打印可选项
    void rendChoice();

    //打印箭头
    void renderFlagChoice(int _choice);

    //擦除箭头
    void eraserFlagChoice(int _choice);

    //选择箭头上移
    void upChoice(int& _choice);

    //选择箭头下移
    void downChoice(int& _choice);



protected:
    virtual void initPropsOnSceneArray() override;
    virtual void renderSceneUI() override;
};

