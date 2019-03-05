#include "CTaskBase.h"

#include "CTaskDirector.h"
#include "CBagDirector.h"


void CTaskBase::enterTaskModde0(CSceneNPC speakNPC, CPosition _pos)
{
    if (speakNPC != provideNpcID)
    {
        return;
    }

    renderMessage(info.c_str(), _pos);

    //CUtils::gotoXY(_pos + CPosition(2, 0));
    //cout << "�Ƿ�������񣨽��� y����";
    //char flag = 0;
    //cin >> flag;

    //CUtils::gotoXY(_pos + CPosition(2, 0));
    //cout << "                              ";

    _getch();

    eraserMessage(_pos);

    CUtils::setColor(142);
    renderBackgroundOfChoice(_pos + CPosition(0, 3));

    int chooiceNum = 0;

    CUtils::moveSelectedUpOrDown(chooiceNum, 2, _pos + CPosition(1, 4), 142, 142);

    CUtils::setColor(0);  //���� ǰ������ ��ɫ
    renderBackgroundOfChoice(_pos + CPosition(1, 3));

    CUtils::setColor();

    if (chooiceNum == 0)
    {
        //ѡ���������
        renderMessage(accept.c_str(), _pos);

        _getch();

        //ȷ�Ͻ�������
        renderMessage(receipt.c_str(), _pos);

        if (taskType == TT_FindNPC)
        {
            taskMode = MODEFINISED;
        }
        else if (taskType == TT_Collect)
        {
            itemCount = CBagDirector::getInstance()->getBag()->getCountItemID(itemID);

            if (itemCount >= itemMax)
            {
                taskMode = MODEFINISED;
            }
            else
            {
                taskMode = MODEUNFINISED;
            }

        }
        else
        {
            taskMode = MODEUNFINISED;
        }

        
        return;
    }
    else
    {
        renderMessage(refuse.c_str(), _pos);
        return;
    }
}

void CTaskBase::enterTaskModde1(CSceneNPC speakNPC, CPosition _pos)
{
    if (speakNPC != regainNpcID)
    {
        return;
    }

    renderMessage(unfiniseded.c_str(), _pos);
}

void CTaskBase::enterTaskModde2(CSceneNPC speakNPC, CPosition _pos)
{
    if (speakNPC != regainNpcID)
    {
        return;
    }

    renderMessage(finished.c_str(), _pos);

    //������� ������
    giveReward();

    taskMode = MODESUBMITED;
}

void CTaskBase::renderMessage(const char* str, CPosition _pos)
{
    //�Ȳ�����ʾ��
    eraserMessage(_pos);

    //��ӡ��Ϣ
    CUtils::gotoXY(_pos);
    while (*str != '\0')
    {
        if (*str == '#')
        {
            _pos = _pos + DI_DOWN;
            CUtils::gotoXY(_pos);

            str++;
            continue;
        }

        cout << *str;
        str++;
    }
}

void CTaskBase::eraserMessage(CPosition _pos)
{
    for (int i = 0; i < 4; i++)
    {
        CUtils::gotoXY(_pos);
        cout << "                                                   ";
        _pos = _pos + DI_DOWN;
    }
}



int CTaskBase::enterTask(CSceneNPC speakNPC, CPosition _pos)
{
    switch (taskMode)
    {
    case MODEUNTAKE:{ enterTaskModde0(speakNPC, _pos); break; }//δ����״̬
    case MODEUNFINISED:{ enterTaskModde1(speakNPC, _pos); break; }//���� ������������
    case MODEFINISED:{ enterTaskModde2(speakNPC, _pos); break; }//�������� ���ύ

    default:  break;
    }

    _getch();

    eraserMessage(_pos);
    return taskMode;
}

CTaskBase::CTaskBase(CTaskID _id)
{
    ID = TI_NONE;
    taskType = TT_NONE;
    name = "";

    provideNpcID = SN_NONE;
    regainNpcID = SN_NONE;

    info = "";
    receipt = "";

    accept = "";
    refuse = "";

    unfiniseded = "";
    finished = "";

    itemID = ID_None;
    itemMax = 0;
    itemCount = 0;

    monsterID = MI_NONE;
    monsterMax = 0;
    monsterCount = 0;


    giveMoney = 0;    //�������
    giveItem = ID_None;  //������Ʒ

    taskMode = 0;      //��ǰ����״̬

    initTaskPropOnXml(_id);
}

CTaskBase::~CTaskBase()
{

}

void CTaskBase::initTaskPropOnXml(CTaskID _id)
{
    //�ļ�·��
    char* filePath = ".\\Resource\\Config\\Task.xml";

    //����XML�ļ�����
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //�����ļ�
        //��ȡxml�ļ��ĸ�Ԫ�� (roleSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //����ÿһ����Ԫ�� (task)
        for (TiXmlElement* taskElement = pSystemElement->FirstChildElement();
            taskElement != nullptr;
            taskElement = taskElement->NextSiblingElement())
        {
            //pTmpElement ����ָ��ÿһ����Ԫ��
            TiXmlAttribute *pTmpAttribute = taskElement->FirstAttribute();
            CTaskID id = (CTaskID)atoi(pTmpAttribute->Value());

            if (id == _id)
            {
                //��������
                for (; pTmpAttribute != nullptr;
                    pTmpAttribute = pTmpAttribute->Next())
                {
                    //pTmpTaskAttribute ����ָ��Ԫ�ص�����
                    if (strcmp(pTmpAttribute->Name(), "id") == 0)                 //���� ID
                    {                                                             
                        ID = (CTaskID)atoi(pTmpAttribute->Value());               
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "TaskType") == 0)      //��������
                    {                                                             
                        taskType = (CTaskType)atoi(pTmpAttribute->Value());       
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "Name") == 0)          //��������
                    {                                                             
                        name = pTmpAttribute->Value();                            
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "ProvideNpcID") == 0)  //������ NPC ID
                    {                                                             
                        provideNpcID = (CSceneNPC)atoi(pTmpAttribute->Value());   
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "RegainNpcID") == 0)   //������ NPC ID
                    {
                        regainNpcID = (CSceneNPC)atoi(pTmpAttribute->Value());
                    }
                }

                //�����ӽڵ�
                for (TiXmlElement* pTmpSubElement = taskElement->FirstChildElement();
                    pTmpSubElement != nullptr;
                    pTmpSubElement = pTmpSubElement->NextSiblingElement())
                {
                    if (strcmp(pTmpSubElement->Value(), "Info") == 0)                  //����������Ϣ
                    {
                        info = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Receipt") == 0)          //ȷ�Ͻ���������Ϣ
                    {
                        receipt = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Accept") == 0)           //��������
                    {
                        accept = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Refuse") == 0)           //�ܾ�����
                    {
                        refuse = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Unfiniseded") == 0)      //���� δ���
                    {
                        unfiniseded = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Finished") == 0)         //���� �����
                    {                                                                     
                        finished = pTmpSubElement->FirstChild()->ToText()->Value();       
                    }
                    //----------------------------------------------------------------------------
                    else if (strcmp(pTmpSubElement->Value(), "ItemID") == 0)         //�ռ���Ʒ
                    {
                        itemID = (CItemID)atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                        itemMax = atoi(pTmpSubElement->FirstAttribute()->Value());
                    }
                    else if (strcmp(pTmpSubElement->Value(), "MonsterID") == 0)         //ɱ����
                    {
                        monsterID = (CMonsterID)atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                        monsterMax = atoi(pTmpSubElement->FirstAttribute()->Value());
                    }
                    //-----------------------------------------------------------------------------
                    else if (strcmp(pTmpSubElement->Value(), "Givemoney") == 0)         //�������
                    {
                        giveMoney = atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                    }
                    else if (strcmp(pTmpSubElement->Value(), "GiveItem") == 0)         //������Ʒ
                    {
                        giveItem = (CItemID)atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                    }


                }


            }
        }
    }
}

void CTaskBase::giveReward()
{
    auto tmpBagDirector = CBagDirector::getInstance();

    //������ռ����� ��Ҫ�Ͻ���Ʒ
    if (taskType == TT_Collect)
    {
        tmpBagDirector->getBag()->giveItemToTask(itemID, itemMax);
    }

    //�������
    if (giveMoney != 0)
    {
        int tmpMoney = tmpBagDirector->getMoney() + giveMoney;

        tmpBagDirector->setMoney(tmpMoney);
        
    }

    //������Ʒ
    if (giveItem != ID_None)
    {
        tmpBagDirector->getBag()->addItem(giveItem);
    }

}
