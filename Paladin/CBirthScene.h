#pragma once
#include "CScene.h"


class CBirthScene : public CScene
{
public:
    CBirthScene();

    ~CBirthScene();

    //��дд���������� ����
    int enterUIScene();


protected:
    //������ӡ����
    void renderSceneUI()override;

    //�ӳ��������ȡ ���� ��Ϣ
    void initPropsOnSceneArray() override;

    //��������
    void renderStory();

    //������ʼ����
    void renderMessage1();

    //���� �Ż� ������
    void renderFindYaHui();

    //NPC �� ��������ƻ�� / ���ظ���ȡ��
    void renderFindJia();

    //NPC �� ������ ��ɱ����
    void renderFindYi();

public:
    //ȷ���Ƿ��һ�γ���
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

