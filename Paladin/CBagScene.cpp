#include "CBagScene.h"

#include "CQiuDao.h"
#include "CYaHui.h"
#include "CTaskDirector.h"

//������ӡ����

 CBagScene::~CBagScene()
{

}

void CBagScene::renderSceneUI()
{

}

 //�ӳ��������ȡ����

  void CBagScene::initPropsOnSceneArray() {}

  CBagScene::CBagScene()
  {
      height = 36;
      width = 36;

      basePos = CPosition(1, 1);

      scenePoint = CPosition(7, 4);
      statePoint = CPosition(5, 27);
      describePoint = CPosition(18, 4);
      helpPoint = CPosition(18, 27);
  }

  int CBagScene::enterUIScene()
  {
      //Ĭ��ѡ���̵�
      int choiceNum = 0;

      //�����̵�
      int res= choiceShop();

      while (true)
      {
          if (res == -1)
          {
              return -1;
          }

          if (res = 1)
          {
              choiceNum++;
              if (choiceNum >= 3)
              {
                  choiceNum = 0;
              }
          }

          if (choiceNum == 0) //0��ʾѡ���̵�
          {
              res = choiceShop();
          }

          if (choiceNum == 1)  //1 ��ʾѡ������
          {
              res = choiceAttribute();
          }

          if (choiceNum == 2)  //2 ��ʾѡ������
          {
              res = choiceTask();
          }

      }

      return -1;
  }

  void CBagScene::renderBorder()
  {
      for (int i = 0; i < describePoint.getX() + 10; i++)
      {
          for (int j = 0; j < statePoint.getY() + 13; j++)
          {
              CUtils::gotoXY(basePos.getX() + i, (basePos.getY() + j) * 2);
              if (i == 0 || i == describePoint.getX() + 10 - 1
                  || j == 0 || j == statePoint.getY() + 13 - 1 || j == statePoint.getY() - 2
                  || ((i == scenePoint.getX() - 3 /*|| i == describePoint.getX() - 1*/) && j < statePoint.getY() - 1)
                  || (j % 5 == 0 && i < scenePoint.getX() - 3 && j < statePoint.getY() - 1))
              {
                  //ȷ���߿���ɫ
                  CUtils::setColor(ColorOfBorder);
                  cout << "��";

              }
              //else if ((i > 0 && i < 4 && j < 6))
              //{
              //    //ȷ�������ɫ
              //    CUtils::setColor(79);
              //    cout << "  ";
              //}
              else if ((i>0 && i < 4 && j < statePoint.getY() - 1))
              {
                  //ȷ�������ɫ
                  CUtils::setColor(42);
                  cout << "  ";
              }
              else
              {
                  //ȷ�������ɫ
                  CUtils::setColor();
                  cout << "  ";
              }
          }

      }

      for (int i = 0; i < 5; i++)
      {
          CUtils::gotoXY(basePos.getX() + 2, (basePos.getY() + 2 + i * 5) * 2);
          CUtils::setColor(112);

          switch (i)
          {
          case 0: { cout << "�̵�"; break; }
          case 1: {cout << "����"; break; }
          case 2: {cout << "����"; break; }
          case 3: {cout << "�浵"; break; }
          case 4: {cout << "�˳�"; break; }
          default:  break;
          }
      }

      CUtils::setColor();
  }

  void CBagScene::renderHelpInfo()
  {
      //�趨��ɫ
      CUtils::setColor(COLEROFHELP);

      CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
      cout << "    ������Ϣ";

      CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
      cout << "  ����ƶ�: ";

      CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
      cout << "    ��     A/a";
      CUtils::gotoXY(helpPoint.getX() + 4, helpPoint.getY() * 2);
      cout << "    ��     D/d";

      CUtils::gotoXY(helpPoint.getX() + 6, helpPoint.getY() * 2);
      cout << "   ȷ ��   Enter";
      CUtils::gotoXY(helpPoint.getX() + 7, helpPoint.getY() * 2);
      cout << "   �� ��   ESC";

      //��ɫ�Ļ�Ĭ��ֵ
      CUtils::setColor();
  }


  //ѡ������

   int CBagScene::choiceAttribute()
  {
      //��ճ���
      system("cls");

      //��ӡ�߿�
      renderBorder();

      //��ӡ������Ϣ
      renderHelpInfo();

      //���Ժ�ɫ��ʾ
      renderRedAttribute();

      //��ӡ ���ɵ�����
      renderQiuXian();

      //��ӡ �Ż� ������
      renderYaHui();

      while (true)
      {
          switch (_getch())
          {
          case '+': {levelUpAll(); break; }  //���ع��ܣ�����ɫ����
          case '\t': {return 1; break; }
          case 27: {return -1; break; }
          default:  break;
          }
      }


      return -1;
  }

  void CBagScene::renderQiuXian()
  {
      //�趨��ӡ��׼��
      CPosition stratPos = scenePoint;

      //��ӡ��ɫ
      CUtils::setColor(142);

      for (int i = 0; i < 19; i++)
      {
          CUtils::gotoXY(stratPos.getX() + i, stratPos.getY() * 2);

          for (int j = 0; j < 9; j++)
          {
              cout << "  ";
          }
      }

      auto tmpRole = CQiuDao::getInstance();

      stratPos = stratPos + CPosition(1, 0);
      CUtils::gotoXY(stratPos );
      cout << " ��  ��  " << tmpRole->getName();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " ��  ��  " << tmpRole->getLevel();

      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " ��  ��  " << tmpRole->getCurEXP()<<"/"<< tmpRole->getMaxEXP();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " H  P  " << tmpRole->getCurHP() << "/" << tmpRole->getMaxHP();

      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " M  P  " << tmpRole->getCurMP() << "/" << tmpRole->getMaxMP();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " ������  " << tmpRole->getReaAttack();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " ������  " << tmpRole->getReaDefence();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " ��  ��  " << tmpRole->getStrength();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " ��  ��  " << tmpRole->getIntelligence();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " ����  " << tmpRole->getAgility();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " �� ��  " ;

      if (tmpRole->getWeaponID() == ID_None)
      {
          cout << "��";
      }
      else
      {
          auto tmpItem = CItemFactory::createItem(tmpRole->getWeaponID());

          cout << tmpItem->name;

          delete tmpItem;
          tmpItem = 0;
      }

      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " �� ��  ";

      if (tmpRole->getGarmentID() == ID_None)
      {
          cout << "��";
      }
      else
      {
          auto tmpItem = CItemFactory::createItem(tmpRole->getGarmentID());

          cout << tmpItem->name;

          delete tmpItem;
          tmpItem = 0;
      }

      CUtils::setColor();
  }

    void CBagScene::renderYaHui()
   {
        auto tmpRole = CYaHui::getInstance();

        //���ڶ��鲻��ӡ
        if (tmpRole->getIsShow() == false)
        {
            return;
        }

       //�趨��ӡ��׼��
       CPosition stratPos = scenePoint + CPosition(0, 11);

       //��ӡ��ɫ
       CUtils::setColor(142);

       for (int i = 0; i < 19; i++)
       {
           CUtils::gotoXY(stratPos.getX() + i, stratPos.getY() * 2);

           for (int j = 0; j < 9; j++)
           {
               cout << "  ";
           }
       }


       stratPos = stratPos + CPosition(1, 0);
       CUtils::gotoXY(stratPos);
       cout << " ��  ��  " << tmpRole->getName();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " ��  ��  " << tmpRole->getLevel();

       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " ��  ��  " << tmpRole->getCurEXP() << "/" << tmpRole->getMaxEXP();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " H  P  " << tmpRole->getCurHP() << "/" << tmpRole->getMaxHP();

       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " M  P  " << tmpRole->getCurMP() << "/" << tmpRole->getMaxMP();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " ������  " << tmpRole->getReaAttack();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " ������  " << tmpRole->getReaDefence();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " ��  ��  " << tmpRole->getStrength();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " ��  ��  " << tmpRole->getIntelligence();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " ����  " << tmpRole->getAgility();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " �� ��  ";

       if (tmpRole->getWeaponID() == ID_None)
       {
           cout << "��";
       }
       else
       {
           auto tmpItem = CItemFactory::createItem(tmpRole->getWeaponID());

           cout << tmpItem->name;

           delete tmpItem;
           tmpItem = 0;
       }

       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " �� ��  ";

       if (tmpRole->getGarmentID() == ID_None)
       {
           cout << "��";
       }
       else
       {
           auto tmpItem = CItemFactory::createItem(tmpRole->getGarmentID());

           cout << tmpItem->name;

           delete tmpItem;
           tmpItem = 0;
       }

       CUtils::setColor();
   }

     void CBagScene::levelUpAll()
    {
         //����������
         auto tmpRole1 = CQiuDao::getInstance();
         tmpRole1->setCurEXP(tmpRole1->getMaxEXP());
         tmpRole1->levelUp();

         //��ӡ���ɵ�����
          renderQiuXian();

         //���Ż�����
         auto tmpRole2 = CYaHui::getInstance();
         tmpRole2->setCurEXP(tmpRole2->getMaxEXP());
         tmpRole2->levelUp();

         //��ӡ�Żݵ�����
          renderYaHui();
    }

  int CBagScene::choiceShop()
  {
      //��ճ���
      system("cls");

      //��ӡ�߿�
      renderBorder();

      //��ӡ������Ϣ
      renderHelpInfo();

      //�̵� ��ɫ��ʾ
      renderRedShop();

      //��ӡ�ֽ���
      renderLine();

      ////��ӡ����
      //CBagDirector::getInstance()->renderBag();

      //��ӡ�̵�
      renderShopStyle();

      auto res = CBagDirector::getInstance()->enterBagSystem();

      //ѭ���л��������̵�
      while (true)
      {
          if (res == -1)
          {
              return -1;
          }
          else if (res == 1)
          {
              res = enterShop();
          }
          else if (res == 10)
          {
              return 1;
          }
          else if (res == 5)
          {
              res = CBagDirector::getInstance()->enterBagSystem();
          }

      }
  }

  int CBagScene::enterShop()
  {
      //ȷ���̵�� �߽� λ��
      CPosition startPos = describePoint + CPosition(2, 1);
      CPosition endPos = startPos + CPosition(6, 16);

      CPosition choiceItem = startPos + CPosition(1, 1);

      renderSelected(choiceItem);

      CPosition tmpPos = choiceItem;

      while (true)
      {
          int keyCode = _getch();
          switch (keyCode)
          {
          case 'a':
          case 'A':{tmpPos = choiceItem + DI_LEFT; break; }
          case 'w':
          case 'W':{tmpPos = choiceItem + DI_UP; break; }
          case 'd':
          case 'D':{tmpPos = choiceItem + DI_RIGHT; break; }
          case 's':
          case 'S':{tmpPos = choiceItem + DI_DOWN; break; }

          case '\r':{buyItem(choiceItem); break; }//������Ʒ

          case 'b':
          case 'B':{eraserItemInfo(); return 5; break; }   // n �л�������

          case '\t':{ eraserItemInfo(); return 10; break; }  // TAB �л�ѡ�

          case 27: {eraserItemInfo(); return -1; }  //Esc -- �˳�����ϵͳ


          }

          //Ŀ����ڷ�Χ�� �ƶ���� ��Ⱦ����
          if (!(tmpPos == choiceItem))
          {
              if (tmpPos.getX() > startPos.getX() && tmpPos.getX() < endPos.getX() - 1
                  && tmpPos.getY() > startPos.getY() && tmpPos.getY() < endPos.getY() - 1)
              {
                  //��ӡ�̵�
                  renderShopStyle();

                  choiceItem = tmpPos;
                  renderSelected(choiceItem);

              }
          }

      }
  }

  void CBagScene::buyItem(CPosition _choice)
  {
      //������������Ʒ��ʾ��Ϣ
      eraserItemInfo();


      //ȷ��ѡ�������
      if (_choice.getX() == describePoint.getX() + 3)
      {
          //ȷ�����ڵĽ�Ǯ��
          int tmpMoney = CBagDirector::getInstance()->getMoney();

          //ȷ��ѡ�����Ʒ
          if (_choice.getY() == describePoint.getY() + 2)
          {
              if (tmpMoney > 100)
              {
                  //��ʼ����
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_HP);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "����һ��ֹѪɢ";


                  //��Ч
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");
              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "Ǯ����������";
              }
          }

          //ȷ��ѡ�����Ʒ
          if (_choice.getY() == describePoint.getY() + 3)
          {
              if (tmpMoney > 120)
              {
                  //��ʼ����
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_MP);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "����һ�ݻ���ɢ";


                  //��Ч
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "Ǯ����������";
              }
          }

          //ȷ��ѡ�����Ʒ
          if (_choice.getY() == describePoint.getY() + 4)
          {
              if (tmpMoney > 500)
              {
                  //��ʼ����
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_Whips);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "����һ������";


                  //��Ч
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "Ǯ����������";
              }
          }

          //ȷ��ѡ�����Ʒ
          if (_choice.getY() == describePoint.getY() + 5)
          {
              if (tmpMoney > 800)
              {
                  //��ʼ����
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_Ioricae);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "����һ������";


                  //��Ч
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "Ǯ����������";
              }
          }

          CUtils::setColor();
          CUtils::gotoXY(statePoint + CPosition(-1, 1));
          cout << "                ";

          CUtils::setColor();
          CUtils::gotoXY(statePoint + CPosition(-1, 1));
          cout << "���н�Ǯ  " << CBagDirector::getInstance()->getMoney();

      }
  }

  void CBagScene::renderSelected(CPosition _pos)
  {
      CUtils::gotoXY(_pos);
      CUtils::setColor(11);
      cout << "��";

      //������������Ʒ��ʾ��Ϣ
      eraserItemInfo();

      if (_pos.getX() == describePoint.getX() + 3)
      {
          CPosition tmpPos = statePoint + DI_RIGHT;
          CUtils::setColor();

          if (_pos.getY() == describePoint.getY() + 2)
          {
              CUtils::gotoXY(tmpPos);
              cout << "ֹѪɢ";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "�ɻָ�һ���� HP";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "�ۼ� 100";
          }
          else if (_pos.getY() == describePoint.getY() + 3)
          {
              CUtils::gotoXY(tmpPos);
              cout << "����ɢ";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "�ɻָ�һ���� MP";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "�ۼ� 120";
          }
          else if (_pos.getY() == describePoint.getY() + 4)
          {
              CUtils::gotoXY(tmpPos);
              cout << "����";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "���ӹ�����";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "�ۼ� 500";
          }
          else if (_pos.getY() == describePoint.getY() + 5)
          {
              CUtils::gotoXY(tmpPos);
              cout << "����";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "���ӷ�����";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "�ۼ� 800";
          }

      }
  }

  void CBagScene::eraserItemInfo()
  {
      CPosition tmpPos = statePoint + DI_RIGHT;
      CUtils::setColor();

      CUtils::gotoXY(tmpPos);
      cout << "                ";

      tmpPos = tmpPos + DI_DOWN;
      CUtils::gotoXY(tmpPos);
      cout << "                ";

      CUtils::gotoXY(tmpPos + DI_DOWN);
      cout << "                ";
  }

  void CBagScene::renderShopStyle()
  {
      CPosition tmpPos = describePoint + CPosition(2, 1);

      for (int i = 0; i < 6; i++)
      {
          for (int j = 0; j < 16; j++)
          {
              //��λҪ��ӡ�� �ط�
              CUtils::gotoXY(tmpPos.getX() + i, (tmpPos.getY() + j) * 2);

              if (i == 0 || i == 5 || j == 0 || j == 15)
              {
                  CUtils::setColor(64);
                  cout << "��";
                  CUtils::setColor();

                  continue;
              }

              if (i == 1 && j == 1)
              {
                  CUtils::setColor(32);
                  cout << "@ ";

                  CUtils::setColor();
                  continue;
              }

              if (i == 1 && j == 2)
              {
                  CUtils::setColor(32);
                  cout << "# ";

                  CUtils::setColor();
                  continue;
              }

              if (i == 1 && j == 3)
              {
                  CUtils::setColor(224);
                  cout << "& ";

                  CUtils::setColor();
                  continue;
              }

              if (i == 1 && j == 4)
              {
                  CUtils::setColor(236);
                  cout << "% ";

                  CUtils::setColor();
                  continue;
              }


              CUtils::setColor();
              cout << "��";

          }
      }
  }

  void CBagScene::renderLine()
  {
      //ȷ��λ��
      CPosition tmpPos;
      tmpPos.setX(describePoint.getX());
      tmpPos.setY(basePos.getY());

      CUtils::gotoXY(tmpPos);

      //ȷ���߿���ɫ
      CUtils::setColor(ColorOfBorder);

      for (int i = 0; i < statePoint.getY() - 1; i++)
      {
          cout << "��";
      }

      CUtils::setColor();
  }

  void CBagScene::renderRedShop()
  {
      CPosition tmpPos = basePos + CPosition(1, 1);

      //ȷ����ɫ
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 2));
      cout << "�̵�";

      CUtils::setColor();
  }

  void CBagScene::renderRedAttribute()
  {
      CPosition tmpPos = basePos + CPosition(1, 6);

      //ȷ����ɫ
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 7));
      cout << "����";

      CUtils::setColor();
  }

  int CBagScene::choiceTask()
  {
      //��ճ���
      system("cls");

      //��ӡ�߿�
      renderBorder();

      //��ӡ������Ϣ
      renderHelpInfo();

      //�����ɫ��ʾ
      renderRedTask();

      //��ӡ�����߿�
      renderTaskBackground();

      //��ӡ������Ϣ
      renderTaskInfo();


      //�л�ѡ�/�˳�
      while (true)
      {
          switch (_getch())
          {
          case '\t': {return 1; break; }
          case 27: {return -1; break; }
          default:  break;
          }
      }


      return -1;
  }

  void CBagScene::renderRedTask()
  {
      CPosition tmpPos = basePos + CPosition(1, 11);

      //ȷ����ɫ
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 12));
      cout << "����";

      CUtils::setColor();
  }

  void CBagScene::renderTaskInfo()
  {
      //�趨��ӡ��׼��
      CPosition stratPos = scenePoint + CPosition(0,-2);

      //�趨��ӡ��ɫ
      CUtils::setColor(142);

      //��ȡ�����б�
      auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();

      //��¼��������
      int countTask = 0;

      for (auto element : (*tmpTaskList))
      {
          CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 2) * 2);
          cout << element->name;

          if (element->taskType != TT_FindNPC)
          {
              CUtils::gotoXY(stratPos.getX() + 1 + countTask * 7, (stratPos.getY() + 8) * 2);
              cout << "����Ҫ��  ";
              if (element->itemID != ID_None)
              {
                  switch (element->itemID)
                  {
                  case ID_Apple:{cout << " ��ƻ�� "; break; }
                  default:  break;
                  }
                  CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 8) * 2);
                  cout << "  ������    " << element->itemCount << "/" << element->itemMax  << endl;
              }
              else if (element->monsterID != MI_NONE)
              {
                  switch (element->monsterID)
                  {
                  case MI_DOG:{cout << "ɱҰ�� "; break;}
                  case MI_PIG:{cout << "ɱҰ�� ";break;}
                  case MI_Devil:{cout << "ɱҰ�� "; break; }
                  default:  break;
                  }
                  CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 8) * 2);
                  cout << "  ������    " << element->monsterCount << "/" << element->monsterMax <<  endl;
              }
          }
          

          CUtils::gotoXY(stratPos.getX() + 3 + countTask * 7, (stratPos.getY() + 8) * 2);
          cout << "���״̬��  ";

          if (element->taskMode == MODEUNFINISED)
          {
              cout << "δ���";
          }
          else if (element->taskMode == MODEFINISED)
          {
              cout << "�����";
          }

          CUtils::gotoXY(stratPos.getX() + 4 + countTask * 7, (stratPos.getY() + 8) * 2);
          cout << "Ŀ�� NPC��  ";

          switch (element->regainNpcID)
          {
          case SN_JIA:{cout << "�� �� ������"; break; }
          case SN_YI:{cout << "�� �� ������"; break; }
          default:  break;
          }

          //����������
          countTask++;
      }

      CUtils::setColor();
  }

  void CBagScene::renderTaskBackground()
  {
      //�趨��ӡ��׼��
      CPosition stratPos = scenePoint+DI_LEFT;

      //��ӡ��ɫ
      CUtils::setColor(142);

      for (int i = 0; i < 3; i++)
      {
          for (int j = 0; j < 6; j++)
          {
              CUtils::gotoXY(stratPos.getX() + j + i * 7, stratPos.getY() * 2);
              for (int k = 0; k < 22; k++)
              {
                  cout << "  ";
              }
          }

          CUtils::gotoXY(stratPos.getX() + 2 + i * 7, (stratPos.getY() + 2) * 2);
          cout << "��";
      }

      CUtils::setColor();
  }
