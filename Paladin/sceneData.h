#pragma once

#include "CPosition.h"

//��������ĸߺͿ�
#define MAXCOL 29
#define MAXROW 33

//�����ĸ߿�
#define COLOFSCENE 20
#define ROWOFSCENE 20

//��������ʼ������
#define BASESCENEPOSX 4
#define BASESCENEPOSY 7

//ս������ 
#define FIGHTSTATEPOINTWIDE 18
#define FIGHTDESRIBEPOINTWIDE 7


#define COLOFBIRTHSCENE 42   //���ִ峡������
#define ROWOFBIRTHSCENE 46

#define COLOFGAMESCENE1 38     //����1 ��������
#define ROWOFGAMESCENE1 41

//��Ұ��Χ
#define DISTANCE 5

#define COLOFGAMESCENE2 20     //����2 ��������
#define ROWOFGAMESCENE2 20

//��ȴ����
#define SAFETYLENGTH 3

#define COLOFGAMESCENE3 20     //����3 ��������
#define ROWOFGAMESCENE3 20


enum CSceneID //������
{
    SI_None,
    SI_WelcomeScene,    //��ӭ����
    SI_BirthScene,      //���ִ峡��
    SI_GameScene1,      //�ؿ�1
    SI_GameScene2,      //�ؿ�2
    SI_GameScene3,      //�ؿ�3
};

enum CSceneTransfer     //���͵�
{
    CI_NONE,

    CI_BirthTOScene1 = 100,  //������ ���� �� ����1  100

    CI_Scene1TOScene2,    //����1 ���� �� �ض�һ��2   101
    CI_Scene1TOScene3,    //����1 ���� �� �ض�����3   102
    CI_Scene1TOBirth,     //����1 ���� �� ������      103

    CI_Scene2TOScene3,    //�ض�һ��2 ���� �� �ض�����3   104
    CI_Scene2TOScene1,    //�ض�һ��2 ���� �� ����1       105

    CI_Scene3TOScene2,    //�ض�����3 ���� �� �ض�һ��2   106
    CI_Scene3TOScene1,    //�ض�����3 ���� �� ����1       107

    CI_FIGHTSCENE = 140,
    CI_WELCOME,


};

enum CSceneNPC //NPC
{
    SN_NONE,
    SN_YAHUI = 150,   //������ �Ż�
    SN_SHOP,          //������ �̵�
    SN_JIA,           //������ ��  152
    SN_YI,            //������ ��  153
};

enum CBirthsceneInfo
{
    BI_PATH = 0,  //�յ�
    BI_BORDER,    //�߿�
    BI_TREE,      //��  
    BI_FENCE,     //դ��
    BI_WINDOW,    //����
    BI_WALL,      //ǽ
    BI_PASS,      //����
    BI_ROOF1,     //�ݶ�1
    BI_ROOF2,     //    2
    BI_ROOF3,     //    3
    BI_ROOF4,     //    4

    BI_BED,       //��
    BI_SARK,      //����

    BI_YAHUIPASS = 25,
    BI_SHOPPASS,

    BI_BIRTH = 30,  //������

    BI_TOSCENE1 = 100,   //���͵�

    BI_YAHUI = 150,   //NPC
    BI_SHOP,
    BI_JIA,
    BI_YI,
};


enum CGameScene1Info
{
    G1_Path = 0,       //  �յ�

    G1_Tree = 2,       //��
    G1_River,        //��
    G1_Ripple1,      //ˮ��1
    G1_Ripple2,      //t
    G1_Bridge,       //��
    G1_ShoalWater,   // ǳˮ

    G1_SmallBox = 10,  //С����
    G1_BigBox,       //����
    G1_HideBx,       //���صı���

    G1_DevilT = 30,    //ħ��ռλ

    G1_Dog = 50,     //��
    G1_Pig,          //��
    G1_Devil ,       //ħ��
  
    

    G1_ToScene2 = 101, //���� �� ����2
    G1_ToScene3,     //���� �� ����3 
    G1_ToBirth,      //���� �� ������
};


enum CGameScene2Info
{
    G2_Path = 0,       //�յ�
    G2_Border,         //�߿�

    G2_SmallBox = 10,  //  С����
    G2_HideBx = 12,    //���صı���

    G2_Dog = 50,     //��
    G2_Pig,          //��

    G2_ToScene3 = 104,     //���� �� ����3 
    G2_ToScene1 ,          //���� �� ����1

};


enum CGameScene3Info
{
    G3_Path = 0,       //�յ�
    G3_Border,         //�߿�

    G3_SmallBox = 10,  //  С����
    G3_HideBx = 12,    //���صı���

    G3_Dog = 50,     //��
    G3_Pig,          //��

    G3_ToScene2 = 106, //���� �� ����2
    G3_ToScene1,       //���� �� ����1 
};

