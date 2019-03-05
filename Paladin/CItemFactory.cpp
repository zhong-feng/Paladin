#include "CItemFactory.h"


CItem* CItemFactory::createItem(CItemID _itemID)
{
    CItem* tmpItem = nullptr;

    switch (_itemID)
    {
    case ID_None:         {tmpItem = new CItem(); break; }

    case ID_HP:         {tmpItem = new CHP(); break; }
    case ID_MP:         {tmpItem = new CMP(); break; }

    case ID_Sword:      {tmpItem = new CSword(); break; }
    case ID_Whips:      {tmpItem = new CWhips(); break; }

    case ID_Ioricae:    {tmpItem = new CIoricae(); break; }
    case ID_Sackcloth:  {tmpItem = new CSackcloth(); break; }

    case ID_Apple:      {tmpItem = new CApple(); break; }

    default:break;
    }

    ////���ݱ���xml�����ļ����г�ʼ��
    initItemPropONxML(_itemID, tmpItem);

    return tmpItem;
}

void CItemFactory::initItemPropONxML(CItemID _itemID, CItem* _pItem)
{
    //�ļ�·��
    char* filePath = ".\\Resource\\Config\\Items.xml";

    //����XML�ļ�����
    TiXmlDocument doc; //DOM

    if (doc.LoadFile(filePath))
    {
        //�����ļ�
        //��ȡxml�ļ��ĸ�Ԫ�� (root)
        TiXmlElement *pRootElement = doc.RootElement();

        //�����ӽڵ㣨item��
        for (auto pItemElement = pRootElement->FirstChildElement();
            pItemElement != nullptr;
            pItemElement = pItemElement->NextSiblingElement())
        {
            //ȷ��ID
            auto pAttribut = pItemElement->FirstAttribute();

            if ((CItemID)atoi(pAttribut->Value()) == _itemID)
            {
                for (pAttribut = pAttribut->Next();
                    pAttribut != nullptr;
                    pAttribut = pAttribut->Next())
                {
                    if (strcmp(pAttribut->Name(), "name") == 0)
                    {
                        _pItem->name = pAttribut->Value();
                    }
                    else if (strcmp(pAttribut->Name(), "desc") == 0)
                    {
                        _pItem->description = pAttribut->Value();
                    }
                    else if (strcmp(pAttribut->Name(), "buyPrice") == 0)
                    {
                        _pItem->buyPrice = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "sellPrice") == 0)
                    {
                        _pItem->sellPrice = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "hp") == 0)
                    {
                        auto pDrugItem = (CDrug*)_pItem;
                        pDrugItem->hp = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "mp") == 0)
                    {
                        auto pDrugItem = (CDrug*)_pItem;
                        pDrugItem->mp = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "defence") == 0)
                    {
                        auto pGarmentItem = (CGarment*)_pItem;
                        pGarmentItem->defence = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "agility") == 0)
                    {
                        auto pGarmentItem = (CGarment*)_pItem;
                        pGarmentItem->agility = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "attack") == 0)
                    {
                        auto pWeaponItem = (CWeapon*)_pItem;
                        pWeaponItem->attack = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "strength") == 0)
                    {
                        auto pWeaponItem = (CWeapon*)_pItem;
                        pWeaponItem->strength = atoi(pAttribut->Value());
                    }
                    else if (strcmp(pAttribut->Name(), "intelligence") == 0)
                    {
                        auto pWeaponItem = (CWeapon*)_pItem;
                        pWeaponItem->intelligence = atoi(pAttribut->Value());
                    }


                }
            }

        }//end for item 

    }//end if ��ʧ��
}
