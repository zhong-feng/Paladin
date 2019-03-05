#pragma once
#include "CScene.h"
class CWelcomeScene :  public CScene
{
public:
    CWelcomeScene();
    ~CWelcomeScene();

    // ͨ�� CScene �̳�
    virtual int enterUIScene() override;

protected:
    //��ӡ�߿�
    void renderBoder();

    //��ӡ���� ��Ч
    void renderRoler();

    //��ӡ��ѡ��
    void rendChoice();

    //��ӡ��ͷ
    void renderFlagChoice(int _choice);

    //������ͷ
    void eraserFlagChoice(int _choice);

    //ѡ���ͷ����
    void upChoice(int& _choice);

    //ѡ���ͷ����
    void downChoice(int& _choice);



protected:
    virtual void initPropsOnSceneArray() override;
    virtual void renderSceneUI() override;
};

