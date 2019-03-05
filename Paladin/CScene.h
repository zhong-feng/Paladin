#pragma once
#include "CPlayer.h"


class CScene
{
public:
    CScene();
    virtual ~CScene();

    //��Ҫ����װ��Һͳ�������Ϸ��������
    virtual int enterUIScene() = 0;


    //��ȡ�͸��� ���������ֵ
    void setValueOfSceneArrayOnPos(CPosition position, int value);
    int getValueOfSceneArrayOnPos(CPosition position);

protected:
    //����txt�ļ���ʼ����������
    void initUISceneArrayOnTextFile(string _name);

    //�ӳ��������ȡ����
    virtual void initPropsOnSceneArray() = 0;

    //������ӡ����
    virtual void renderSceneUI() = 0;

    //�������λ��ȷ����ӡ��׼��
    bool setBasePosByBirthPos();

    //��ӡ�߿�
     void renderBoder();

    //��ӡ������Ϣ
    void renderHelpInfo();

    //��ӡ ������ �¼�
    void renderMessage(const char* str);

    //���� �¼���Ϣ
    void eraserMessage();

    //��ӡ�������λ��
    void rendPlayerPos();

    //��Ⱦ�����Ϣ
    void rendScenePlayer();

    //������Ʒ
    void dropItem();

protected:
    //���� ID
    GS_SYNTHESIZE(CSceneID, sceneID, SceneID);

    GS_SYNTHESIZE(string, name, Name);

    //�������Ϳ�
    GS_SYNTHESIZE(int, height, Height);  //��
    GS_SYNTHESIZE(int, width, Width);    //��

    //����UI��Ӧ�߼�����
    int** ppSceneArray;  //��̬���� ��ά��������

    //������ӡ ��׼��
    GS_SYNTHESIZE(CPosition, basePos, BasePos);

    //�������������ı������
    GS_SYNTHESIZE(CPosition, scenePoint, ScenePoint);
    GS_SYNTHESIZE(CPosition, statePoint, StatePoint);
    GS_SYNTHESIZE(CPosition, describePoint, DescribePoint);
    GS_SYNTHESIZE(CPosition, helpPoint, HelpPoint);

    //������Ϣ
    GS_SYNTHESIZE(CPlayer, player, Player);

    //��Ϣ���ֵ�ʱ��
    DWORD dwPreMessage;
   

};

