#pragma once
#include "CScene.h"
class CFightScene :
    public CScene
{
public:
    CFightScene();
    ~CFightScene();

    //��ӡ�߿�
    void renderBoder();

    //��ӡ������Ϣ
    void renderHelpInfo();
    
    //��д���ി�麯��
    void initPropsOnSceneArray();//�ӳ��������ȡ����
    void renderSceneUI();//������ӡ����
    int enterUIScene();//��Ҫ����װ��Һͳ�������Ϸ��������

public:
    list<string> fightInfoList;

};

