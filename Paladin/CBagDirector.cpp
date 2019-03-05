#include "CBagDirector.h"

#include "CBagScene.h"
#include "CQiuDao.h"
#include "CYaHui.h"

int CBagDirector::money = 0;

 CBagDirector::CBagDirector()
{
    m_pBag = 0;
    pointOfBagStartRender = CPosition(0, 0);
    pointOfShowItemInfo = CPosition(0, 0);
    pointOfShowHelpInfo = CPosition(0, 0);

    //����ϵͳ�ĳ�ʼ��
    onInit();
}

  CBagDirector::~CBagDirector()
 {
     if (m_pBag)
     {
         delete m_pBag;
         m_pBag = 0;
     }
 }

  //���뱳��ϵͳ

   int CBagDirector::enterBagSystem()
  {
       //��ӡ������Ϣ
       renderHelpInfo();

      //����ϵͳ����Ⱦ����--------------
      renderBagSystemUI();

      while (true)
      {

          int keyCode = _getch();
          switch (keyCode)
          {

          case 'a':
          case 'A': { moveSelectedCursor(DI_LEFT);  break; }  //�ƶ�ѡ����
          case 'd':
          case 'D': { moveSelectedCursor(DI_RIGHT);  break; }
          case 'w':
          case 'W': { moveSelectedCursor(DI_UP);  break; }
          case 's':
          case 'S': { moveSelectedCursor(DI_DOWN);  break; }

          case '1': { randomAddItem();  break; }//��������Ʒ

          case '\r': { enterSelectedCurosor();  break; }//ʹ����Ʒ

          case 'n':
          case 'N':{ eraserItemInfo(); return 1; break; }   // n �л����̵�
          case '\t':{ eraserItemInfo(); return 10; break; }  // TAB �л�ѡ�

          case 27: { eraserItemInfo(); return -1; }  //Esc -- �˳�����ϵͳ
          }

          //����ϵͳ�ĵ���Ⱦ����
          renderBagSystemUI();
      }

  }

    int CBagDirector::getMoney()
   {
       return money;
   }

     void CBagDirector::setMoney(int _num)
    {
        money = _num;
    }

   //����ϵͳ����Ⱦ����--------------

    void CBagDirector::renderBagSystemUI()
    {
        //��ӡ������Ϣ
        renderBag();

        //��ӡ��Ǯ
        CUtils::gotoXY(pointOfShowItemInfo+DI_UP);
        cout << "���н�Ǯ  " << money << endl;;

        //��ӡѡ����
       selectedCursor.render(pointOfBagStartRender + selectedCursor.pos);

       //��ӡ��Ʒ��ʾ��Ϣ
       displaySelectedItemInfo();
   }

//ʹ�ù��ѡ�����Ʒ
 void CBagDirector::useTheSelectedCursorItem()
{
    //ȷ��ʹ�õ���ƷID
    auto useItemID = m_pBag->useItem(selectedCursor.pos);

    //������ʹ�õ���Ʒֱ�ӷ���
    if (useItemID == ID_None)
    {
        return;
    }

    //1.ȷ��ʹ�ö���-----------------------------------

    //��Ⱦ ѡ�� ������(���ؿ�ѡ���� Ĭ��ѡ����)
    int maxCount = renderChoiceUIScene();
    int choiceNum = 0;

    //ȷ��ѡ�����
    CUtils::moveSelectedUpOrDown(choiceNum, maxCount, CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 2), 124, 193);

    //����ѡ����
    eraserChoiceUIScene();

    CRole* tmpRole = nullptr;
    if (choiceNum == 0)
    {
        tmpRole = CQiuDao::getInstance();
    }
    else
    {
        tmpRole = CYaHui::getInstance();
    }

    // 2. ȷ��ʹ�� ���----------------------
    auto tmpIten = CItemFactory::createItem(useItemID);

    switch (tmpIten->type)
    {
    case IT_Drug: { tmpIten->useItem(tmpRole); break; }
    case IT_Weapon: {useWeapon(tmpIten, tmpRole); break; }
    case IT_Garment: { useGarment(tmpIten, tmpRole); break; }
    default: break;
    }

    
    delete tmpIten;
    tmpIten = 0;
}

 //����ѡ����
void CBagDirector::eraserChoiceUIScene()
 {
    eraserMessageUIScence();
 }

//����ϵͳ�ĳ�ʼ��

 void CBagDirector::onInit()
{
    //�ӱ���������ȡ������������
    CBagScene* tmpScene = new CBagScene();

    //������ӡ������
    pointOfBagStartRender = tmpScene->getScenePoint()+CPosition(0,1);
    pointOfShowItemInfo = tmpScene->getStatePoint() + CPosition(0, 1);
    pointOfShowHelpInfo = tmpScene->getHelpPoint();

    //���Ĭ���ڵ�һ��λ��
    selectedCursor.pos = CPosition(1, 1);

    //������������
    m_pBag = new CBag();

    delete tmpScene;
    tmpScene = 0;
}

//��Ⱦ ѡ�� ������(���ؿ�ѡ����)
int CBagDirector::renderChoiceUIScene()
{
    renderMessageUIScence();

    //��Ⱦ ����

    //ȷ����ɫ
    CUtils::setColor(110);

    CUtils::gotoXY(CPosition( BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 3 ));
    cout << CQiuDao::getInstance()->getName();

    int max = 1;

    //��Ⱦ �Ż�

    //ȷ��λ��
    CUtils::gotoXY(CPosition( BAGPROMPTPOSX + 3, BAGPROMPTPOSY + 3 ));

    //ȷ�ϸ������
    if (CYaHui::getInstance()->getIsShow())
    {
        max++;
    }
    else
    {
        //ȷ����ɫ
        CUtils::setColor(103);
    }
    cout << CYaHui::getInstance()->getName();

    //Ĭ��ѡ�� ����
    CUtils::setColor(193);
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 2, BAGPROMPTPOSY + 2 ));
    cout << "��" << endl;

    CUtils::setColor();

    return max;
}

void CBagDirector::renderBag()
{
    //��������Ⱦ
    m_pBag->renderBagUI(pointOfBagStartRender);
}

void CBagDirector::enterSelectedCurosor()
{
    //��ȷ����Ʒ���Բ���
    auto tmpItemID = m_pBag->getBagUnit(selectedCursor.pos)->getID();
    if (tmpItemID == ID_None)
    {
        return;
    }

    //��Ⱦ ѡ�� ��ʲô
    renderMessageUIScence();

    //��ѡ�б����ؿ�ѡ���ֵ��
    int maxNum = renderCanChoiceList();
    int choiceNum = 0;

    //ȷ��ѡ�����
    CUtils::moveSelectedUpOrDown(choiceNum, maxNum, CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 2), 124, 193);

    //���� ѡ�� ����
    eraserMessageUIScence();

    switch (choiceNum)
    {
    case 0: {return; break; }//����
    case 1: {saleItem(); break; }//����
    case 2: {castOffItem(); break; }//����
    case 3: {useTheSelectedCursorItem(); break; }//ʹ��
    default: break;
    }

    return;
}

void CBagDirector::castOffItem()
{
    //ȷ����Ԫ��
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //���ĵ�Ԫ������ ������Ʒ
    tmpBagUnit->setCount(0);
    tmpBagUnit->setID(ID_None);
}

void CBagDirector::saleItem()
{
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //ȷ������
    auto tmpNum = tmpBagUnit->getCount();

    //ȷ������
    auto tmpItem = CItemFactory::createItem(tmpBagUnit->getID());
    auto tmpSellPrice = tmpItem->sellPrice;

    //�ͷ���ʱ����
    delete tmpItem;
    tmpItem = 0;

    money += tmpSellPrice * tmpNum;

    tmpBagUnit->setCount(0);
    tmpBagUnit->setID(ID_None);

    //��Ч
    CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\sell.wma");

}

int CBagDirector::renderCanChoiceList()
{
    //ȷ����ɫ
    CUtils::setColor(110);

    //ȷ����ѡ���ӡ����
    CPosition tmpPos = CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 3);

    //������������ѡ����
    int tmpMaxNum = 0;

    CUtils::gotoXY(tmpPos);
    cout << "����";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    CUtils::gotoXY(tmpPos);
    cout << "����";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    CUtils::gotoXY(tmpPos);
    cout << "����";
    tmpMaxNum++;
    tmpPos = tmpPos + DI_DOWN;

    //ȷ���Ƿ����ʹ��
    auto tmpItemID = m_pBag->getBagUnit(selectedCursor.pos)->getID();
    if (tmpItemID > 0 && tmpItemID < ID_Apple)
    {
        CUtils::gotoXY(tmpPos);
        cout << "ʹ��";
        tmpMaxNum++;
    }

    //ѡ���һ��ΪĬ��ѡ����
    //Ĭ��ѡ�� ����
    CUtils::setColor(193);
    CUtils::gotoXY(CPosition(BAGPROMPTPOSX + 1, BAGPROMPTPOSY + 2));
    cout << "��" << endl;

    CUtils::setColor();

    return tmpMaxNum;
}

void CBagDirector::useWeapon(CItem* _weapon, CRole* _role)
{
    //����װ��������ж��
    if (_role->getWeaponID() != ID_None)
    {
        auto tmpItem = CItemFactory::createItem(_role->getWeaponID());

        tmpItem->putDownEquipment(_role);

        m_pBag->addItem(tmpItem->id);

        delete tmpItem;
        tmpItem = 0;
    }

    //װ������
    _weapon->useItem(_role);
    _role->setWeaponID(_weapon->id);
}

void CBagDirector::useGarment(CItem* _garment, CRole* _role)
{
    //����װ���� ���� ж��
    if (_role->getGarmentID() != ID_None)
    {
        auto tmpItem = CItemFactory::createItem(_role->getGarmentID());

        tmpItem->putDownEquipment(_role);
        m_pBag->addItem(tmpItem->id);

        delete tmpItem;
        tmpItem = 0;
    }

    //װ�� ����
    _garment->useItem(_role);
    _role->setGarmentID(_garment->id);
}

void CBagDirector::renderMessageUIScence()
{
    //ȷ����ɫ
    CUtils::setColor(124);

    //��Ⱦ�߿� ����
    for (int i = 0; i < COLOFMESSAGE; i++)
    {
        for (int j = 0; j < ROWOFMESSAGE; j++)
        {
            CUtils::gotoXY(CPosition(BAGPROMPTPOSX + i, BAGPROMPTPOSY + j));
            if (i == 0 || i == COLOFMESSAGE - 1)
            {
                cout << "==";
                continue;
            }
            if (j == 0 || j == ROWOFMESSAGE - 1)
            {
                cout << "||";
                continue;
            }

            cout << "  ";
        }
    }

    CUtils::setColor();
}

void CBagDirector::eraserMessageUIScence()
{
    CUtils::setColor();

    for (int i = 0; i < COLOFMESSAGE; i++)
    {
        for (int j = 0; j < ROWOFMESSAGE; j++)
        {
            CUtils::gotoXY(CPosition(BAGPROMPTPOSX + i, BAGPROMPTPOSY + j));
            cout << "  ";
        }
    }
}

void CBagDirector::randomAddItem()
{
    int randomItem = (rand()*rand() + rand()) % 7;
    int randomNum = (rand()*rand() + rand()) % 3 + 1;

    switch (randomItem)
    {
    case 0: { m_pBag->addItem(ID_HP, randomNum); break; }
    case 1: { m_pBag->addItem(ID_MP, randomNum); break; }
    case 2: { m_pBag->addItem(ID_Sword, randomNum); break; }
    case 3: { m_pBag->addItem(ID_Whips, randomNum); break; }
    case 4: { m_pBag->addItem(ID_Ioricae, randomNum); break; }
    case 5: { m_pBag->addItem(ID_Sackcloth, randomNum); break; }
    case 6: { m_pBag->addItem(ID_Apple, randomNum); break; }

    default: break;
    }
}

void CBagDirector::moveSelectedCursor(CDirection _direction)
{
    CPosition nextPos = selectedCursor.pos + _direction;

    //�߽��ж�
    if (nextPos.x < 1 || nextPos.x > m_pBag->getRow() - 2
        || nextPos.y < 1 || nextPos.y > m_pBag->getCol() - 2)
    {
        return;
    }
    else
    {
        selectedCursor.pos = nextPos;
    }
}

void CBagDirector::eraserItemInfo()
{
    for (int i = 0; i < 10; i++)
    {
        CUtils::gotoXY(pointOfShowItemInfo.getX() + i, pointOfShowItemInfo.getY() * 2);
        cout << "                    ";
    }
}

void CBagDirector::renderHelpInfo()
{
    //�趨��ɫ
    CUtils::setColor(COLEROFHELP);

    CUtils::gotoXY(pointOfShowHelpInfo.getX(), pointOfShowHelpInfo.getY() * 2);
    cout << "    ������Ϣ";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 2, pointOfShowHelpInfo.getY() * 2);
    cout << "  ����ƶ�: ";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 3, pointOfShowHelpInfo.getY() * 2);
    cout << "  ��/��    A/D";
    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 4, pointOfShowHelpInfo.getY() * 2);
    cout << "  ��/��    W/S";

    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 6, pointOfShowHelpInfo.getY() * 2);
    cout << "   ȷ ��   Enter";
    CUtils::gotoXY(pointOfShowHelpInfo.getX() + 7, pointOfShowHelpInfo.getY() * 2);
    cout << "   �� ��   ESC";

    //��ɫ�Ļ�Ĭ��ֵ
    CUtils::setColor();
}

void CBagDirector::displaySelectedItemInfo()
{
    //���֮ǰ����Ⱦ
    eraserItemInfo();

    //ȷ����Ԫ��
    auto tmpBagUnit = m_pBag->getBagUnit(selectedCursor.pos);

    //���ݵ�Ԫ��ȷ����Ʒ
    auto pTmpItem = CItemFactory::createItem(tmpBagUnit->getID());

    if (tmpBagUnit->getCount() == 0)
    {
        CUtils::gotoXY(pointOfShowItemInfo);
        cout << "��";
    }
    else
    {
        CUtils::gotoXY(pointOfShowItemInfo);
        cout << "����  " << tmpBagUnit->getCount() << endl;

        pTmpItem->renderItemInfo(pointOfShowItemInfo + DI_DOWN);
    }

    delete pTmpItem;
    pTmpItem = 0;
}

CBag* CBagDirector::getBag()
{
    return m_pBag;
}
