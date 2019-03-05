#pragma once
#include "utility.h"
#include "CUtils.h"
#include "CSingleton.h"

//������С
#define COLOFBAG 16
#define ROLOFBAG 10

#define BAGPROMPTPOSX 11
#define BAGPROMPTPOSY 11

#define COLOFMESSAGE 7
#define ROWOFMESSAGE 9

enum CItemID //��ƷID
{
    ID_None,
    ID_HP = 1,        //HPҩˮ ҩƷ
    ID_MP,            //
                      
    ID_Sword = 10,    //��  ����
    ID_Whips,         //����
                      
    ID_Ioricae = 20,    //����  �·�
    ID_Sackcloth,       //����
                      
    ID_Apple=30,         //ƻ��  ������Ʒ

};


enum CItemType
{
    IT_None,     //�� ֵ
    IT_Drug,     //ҩƷ
    IT_Weapon,   //����
    IT_Garment,  //�·�
    IT_Task,     //������Ʒ
};
