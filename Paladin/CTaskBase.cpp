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
    //cout << "是否接受任务（接受 y）：";
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

    CUtils::setColor(0);  //背景 前景都是 黑色
    renderBackgroundOfChoice(_pos + CPosition(1, 3));

    CUtils::setColor();

    if (chooiceNum == 0)
    {
        //选择接受任务
        renderMessage(accept.c_str(), _pos);

        _getch();

        //确认接受任务
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

    //完成任务 给奖励
    giveReward();

    taskMode = MODESUBMITED;
}

void CTaskBase::renderMessage(const char* str, CPosition _pos)
{
    //先擦除提示框
    eraserMessage(_pos);

    //打印消息
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
    case MODEUNTAKE:{ enterTaskModde0(speakNPC, _pos); break; }//未接受状态
    case MODEUNFINISED:{ enterTaskModde1(speakNPC, _pos); break; }//接受 但条件不满足
    case MODEFINISED:{ enterTaskModde2(speakNPC, _pos); break; }//条件满足 待提交

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


    giveMoney = 0;    //奖励金币
    giveItem = ID_None;  //奖励物品

    taskMode = 0;      //当前任务状态

    initTaskPropOnXml(_id);
}

CTaskBase::~CTaskBase()
{

}

void CTaskBase::initTaskPropOnXml(CTaskID _id)
{
    //文件路径
    char* filePath = ".\\Resource\\Config\\Task.xml";

    //创建XML文件对象
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //解析文件
        //获取xml文件的根元素 (roleSystem)
        TiXmlElement *pSystemElement = doc.RootElement();

        //遍历每一个子元素 (task)
        for (TiXmlElement* taskElement = pSystemElement->FirstChildElement();
            taskElement != nullptr;
            taskElement = taskElement->NextSiblingElement())
        {
            //pTmpElement 依次指向每一个子元素
            TiXmlAttribute *pTmpAttribute = taskElement->FirstAttribute();
            CTaskID id = (CTaskID)atoi(pTmpAttribute->Value());

            if (id == _id)
            {
                //遍历属性
                for (; pTmpAttribute != nullptr;
                    pTmpAttribute = pTmpAttribute->Next())
                {
                    //pTmpTaskAttribute 依次指向元素的属性
                    if (strcmp(pTmpAttribute->Name(), "id") == 0)                 //任务 ID
                    {                                                             
                        ID = (CTaskID)atoi(pTmpAttribute->Value());               
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "TaskType") == 0)      //任务类型
                    {                                                             
                        taskType = (CTaskType)atoi(pTmpAttribute->Value());       
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "Name") == 0)          //任务名称
                    {                                                             
                        name = pTmpAttribute->Value();                            
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "ProvideNpcID") == 0)  //接任务 NPC ID
                    {                                                             
                        provideNpcID = (CSceneNPC)atoi(pTmpAttribute->Value());   
                    }                                                             
                    else if (strcmp(pTmpAttribute->Name(), "RegainNpcID") == 0)   //还任务 NPC ID
                    {
                        regainNpcID = (CSceneNPC)atoi(pTmpAttribute->Value());
                    }
                }

                //遍历子节点
                for (TiXmlElement* pTmpSubElement = taskElement->FirstChildElement();
                    pTmpSubElement != nullptr;
                    pTmpSubElement = pTmpSubElement->NextSiblingElement())
                {
                    if (strcmp(pTmpSubElement->Value(), "Info") == 0)                  //发布任务信息
                    {
                        info = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Receipt") == 0)          //确认接受任务信息
                    {
                        receipt = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Accept") == 0)           //接受任务
                    {
                        accept = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Refuse") == 0)           //拒绝任务
                    {
                        refuse = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Unfiniseded") == 0)      //任务 未完成
                    {
                        unfiniseded = pTmpSubElement->FirstChild()->ToText()->Value();
                    }
                    else if (strcmp(pTmpSubElement->Value(), "Finished") == 0)         //任务 已完成
                    {                                                                     
                        finished = pTmpSubElement->FirstChild()->ToText()->Value();       
                    }
                    //----------------------------------------------------------------------------
                    else if (strcmp(pTmpSubElement->Value(), "ItemID") == 0)         //收集物品
                    {
                        itemID = (CItemID)atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                        itemMax = atoi(pTmpSubElement->FirstAttribute()->Value());
                    }
                    else if (strcmp(pTmpSubElement->Value(), "MonsterID") == 0)         //杀怪物
                    {
                        monsterID = (CMonsterID)atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                        monsterMax = atoi(pTmpSubElement->FirstAttribute()->Value());
                    }
                    //-----------------------------------------------------------------------------
                    else if (strcmp(pTmpSubElement->Value(), "Givemoney") == 0)         //奖励金币
                    {
                        giveMoney = atoi(pTmpSubElement->FirstChild()->ToText()->Value());
                    }
                    else if (strcmp(pTmpSubElement->Value(), "GiveItem") == 0)         //奖励物品
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

    //如果是收集任务 就要上交物品
    if (taskType == TT_Collect)
    {
        tmpBagDirector->getBag()->giveItemToTask(itemID, itemMax);
    }

    //奖励金币
    if (giveMoney != 0)
    {
        int tmpMoney = tmpBagDirector->getMoney() + giveMoney;

        tmpBagDirector->setMoney(tmpMoney);
        
    }

    //奖励物品
    if (giveItem != ID_None)
    {
        tmpBagDirector->getBag()->addItem(giveItem);
    }

}
