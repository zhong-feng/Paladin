#include "CBagScene.h"

#include "CQiuDao.h"
#include "CYaHui.h"
#include "CTaskDirector.h"

//场景打印函数

 CBagScene::~CBagScene()
{

}

void CBagScene::renderSceneUI()
{

}

 //从场景数组读取配置

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
      //默认选择商店
      int choiceNum = 0;

      //进入商店
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

          if (choiceNum == 0) //0表示选择商店
          {
              res = choiceShop();
          }

          if (choiceNum == 1)  //1 表示选择属性
          {
              res = choiceAttribute();
          }

          if (choiceNum == 2)  //2 表示选择任务
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
                  //确定边框颜色
                  CUtils::setColor(ColorOfBorder);
                  cout << "◆";

              }
              //else if ((i > 0 && i < 4 && j < 6))
              //{
              //    //确定填充颜色
              //    CUtils::setColor(79);
              //    cout << "  ";
              //}
              else if ((i>0 && i < 4 && j < statePoint.getY() - 1))
              {
                  //确定填充颜色
                  CUtils::setColor(42);
                  cout << "  ";
              }
              else
              {
                  //确定填充颜色
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
          case 0: { cout << "商店"; break; }
          case 1: {cout << "属性"; break; }
          case 2: {cout << "任务"; break; }
          case 3: {cout << "存档"; break; }
          case 4: {cout << "退出"; break; }
          default:  break;
          }
      }

      CUtils::setColor();
  }

  void CBagScene::renderHelpInfo()
  {
      //设定颜色
      CUtils::setColor(COLEROFHELP);

      CUtils::gotoXY(helpPoint.getX(), helpPoint.getY() * 2);
      cout << "    帮助信息";

      CUtils::gotoXY(helpPoint.getX() + 2, helpPoint.getY() * 2);
      cout << "  光标移动: ";

      CUtils::gotoXY(helpPoint.getX() + 3, helpPoint.getY() * 2);
      cout << "    左     A/a";
      CUtils::gotoXY(helpPoint.getX() + 4, helpPoint.getY() * 2);
      cout << "    右     D/d";

      CUtils::gotoXY(helpPoint.getX() + 6, helpPoint.getY() * 2);
      cout << "   确 认   Enter";
      CUtils::gotoXY(helpPoint.getX() + 7, helpPoint.getY() * 2);
      cout << "   退 出   ESC";

      //颜色改回默认值
      CUtils::setColor();
  }


  //选择属性

   int CBagScene::choiceAttribute()
  {
      //清空场景
      system("cls");

      //打印边框
      renderBorder();

      //打印帮助信息
      renderHelpInfo();

      //属性红色表示
      renderRedAttribute();

      //打印 求仙的属性
      renderQiuXian();

      //打印 雅惠 的属性
      renderYaHui();

      while (true)
      {
          switch (_getch())
          {
          case '+': {levelUpAll(); break; }  //隐藏功能，给角色升级
          case '\t': {return 1; break; }
          case 27: {return -1; break; }
          default:  break;
          }
      }


      return -1;
  }

  void CBagScene::renderQiuXian()
  {
      //设定打印基准点
      CPosition stratPos = scenePoint;

      //打印底色
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
      cout << " 姓  名  " << tmpRole->getName();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " 等  级  " << tmpRole->getLevel();

      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " 经  验  " << tmpRole->getCurEXP()<<"/"<< tmpRole->getMaxEXP();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " H  P  " << tmpRole->getCurHP() << "/" << tmpRole->getMaxHP();

      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " M  P  " << tmpRole->getCurMP() << "/" << tmpRole->getMaxMP();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " 攻击力  " << tmpRole->getReaAttack();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " 防御力  " << tmpRole->getReaDefence();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " 力  量  " << tmpRole->getStrength();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " 智  力  " << tmpRole->getIntelligence();
      stratPos = stratPos + DI_DOWN;
      CUtils::gotoXY(stratPos);
      cout << " 敏捷  " << tmpRole->getAgility();

      stratPos = stratPos + CPosition(2, 0);
      CUtils::gotoXY(stratPos);
      cout << " 武 器  " ;

      if (tmpRole->getWeaponID() == ID_None)
      {
          cout << "空";
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
      cout << " 衣 服  ";

      if (tmpRole->getGarmentID() == ID_None)
      {
          cout << "空";
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

        //不在队伍不打印
        if (tmpRole->getIsShow() == false)
        {
            return;
        }

       //设定打印基准点
       CPosition stratPos = scenePoint + CPosition(0, 11);

       //打印底色
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
       cout << " 姓  名  " << tmpRole->getName();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " 等  级  " << tmpRole->getLevel();

       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " 经  验  " << tmpRole->getCurEXP() << "/" << tmpRole->getMaxEXP();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " H  P  " << tmpRole->getCurHP() << "/" << tmpRole->getMaxHP();

       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " M  P  " << tmpRole->getCurMP() << "/" << tmpRole->getMaxMP();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " 攻击力  " << tmpRole->getReaAttack();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " 防御力  " << tmpRole->getReaDefence();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " 力  量  " << tmpRole->getStrength();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " 智  力  " << tmpRole->getIntelligence();
       stratPos = stratPos + DI_DOWN;
       CUtils::gotoXY(stratPos);
       cout << " 敏捷  " << tmpRole->getAgility();

       stratPos = stratPos + CPosition(2, 0);
       CUtils::gotoXY(stratPos);
       cout << " 武 器  ";

       if (tmpRole->getWeaponID() == ID_None)
       {
           cout << "空";
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
       cout << " 衣 服  ";

       if (tmpRole->getGarmentID() == ID_None)
       {
           cout << "空";
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
         //给求仙升级
         auto tmpRole1 = CQiuDao::getInstance();
         tmpRole1->setCurEXP(tmpRole1->getMaxEXP());
         tmpRole1->levelUp();

         //打印求仙的属性
          renderQiuXian();

         //给雅惠升级
         auto tmpRole2 = CYaHui::getInstance();
         tmpRole2->setCurEXP(tmpRole2->getMaxEXP());
         tmpRole2->levelUp();

         //打印雅惠的属性
          renderYaHui();
    }

  int CBagScene::choiceShop()
  {
      //清空场景
      system("cls");

      //打印边框
      renderBorder();

      //打印帮助信息
      renderHelpInfo();

      //商店 红色显示
      renderRedShop();

      //打印分界线
      renderLine();

      ////打印背包
      //CBagDirector::getInstance()->renderBag();

      //打印商店
      renderShopStyle();

      auto res = CBagDirector::getInstance()->enterBagSystem();

      //循环切换背包和商店
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
      //确定商店的 边界 位置
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

          case '\r':{buyItem(choiceItem); break; }//购买物品

          case 'b':
          case 'B':{eraserItemInfo(); return 5; break; }   // n 切换到背包

          case '\t':{ eraserItemInfo(); return 10; break; }  // TAB 切换选项卡

          case 27: {eraserItemInfo(); return -1; }  //Esc -- 退出背包系统


          }

          //目标点在范围内 移动光标 渲染场景
          if (!(tmpPos == choiceItem))
          {
              if (tmpPos.getX() > startPos.getX() && tmpPos.getX() < endPos.getX() - 1
                  && tmpPos.getY() > startPos.getY() && tmpPos.getY() < endPos.getY() - 1)
              {
                  //打印商店
                  renderShopStyle();

                  choiceItem = tmpPos;
                  renderSelected(choiceItem);

              }
          }

      }
  }

  void CBagScene::buyItem(CPosition _choice)
  {
      //擦除遗留的物品提示信息
      eraserItemInfo();


      //确定选择光标的行
      if (_choice.getX() == describePoint.getX() + 3)
      {
          //确定现在的金钱数
          int tmpMoney = CBagDirector::getInstance()->getMoney();

          //确定选择的物品
          if (_choice.getY() == describePoint.getY() + 2)
          {
              if (tmpMoney > 100)
              {
                  //开始买东西
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_HP);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "购买一份止血散";


                  //音效
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");
              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "钱不够，买不了";
              }
          }

          //确定选择的物品
          if (_choice.getY() == describePoint.getY() + 3)
          {
              if (tmpMoney > 120)
              {
                  //开始买东西
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_MP);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "购买一份回气散";


                  //音效
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "钱不够，买不了";
              }
          }

          //确定选择的物品
          if (_choice.getY() == describePoint.getY() + 4)
          {
              if (tmpMoney > 500)
              {
                  //开始买东西
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_Whips);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "购买一条长鞭";


                  //音效
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "钱不够，买不了";
              }
          }

          //确定选择的物品
          if (_choice.getY() == describePoint.getY() + 5)
          {
              if (tmpMoney > 800)
              {
                  //开始买东西
                  CBagDirector::getInstance()->setMoney(tmpMoney - 100);
                  CBagDirector::getInstance()->getBag()->addItem(ID_Ioricae);

                  CUtils::setColor(10);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "购买一件铠甲";


                  //音效
                  CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\buy.wma");

              }
              else
              {
                  CUtils::setColor(12);
                  CUtils::gotoXY(statePoint + DI_RIGHT);
                  cout << "钱不够，买不了";
              }
          }

          CUtils::setColor();
          CUtils::gotoXY(statePoint + CPosition(-1, 1));
          cout << "                ";

          CUtils::setColor();
          CUtils::gotoXY(statePoint + CPosition(-1, 1));
          cout << "现有金钱  " << CBagDirector::getInstance()->getMoney();

      }
  }

  void CBagScene::renderSelected(CPosition _pos)
  {
      CUtils::gotoXY(_pos);
      CUtils::setColor(11);
      cout << "◇";

      //擦除遗留的物品提示信息
      eraserItemInfo();

      if (_pos.getX() == describePoint.getX() + 3)
      {
          CPosition tmpPos = statePoint + DI_RIGHT;
          CUtils::setColor();

          if (_pos.getY() == describePoint.getY() + 2)
          {
              CUtils::gotoXY(tmpPos);
              cout << "止血散";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "可恢复一定的 HP";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "售价 100";
          }
          else if (_pos.getY() == describePoint.getY() + 3)
          {
              CUtils::gotoXY(tmpPos);
              cout << "回气散";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "可恢复一定的 MP";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "售价 120";
          }
          else if (_pos.getY() == describePoint.getY() + 4)
          {
              CUtils::gotoXY(tmpPos);
              cout << "长鞭";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "增加攻击力";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "售价 500";
          }
          else if (_pos.getY() == describePoint.getY() + 5)
          {
              CUtils::gotoXY(tmpPos);
              cout << "铠甲";

              tmpPos = tmpPos + DI_DOWN;
              CUtils::gotoXY(tmpPos);
              cout << "增加防御力";

              CUtils::gotoXY(tmpPos + DI_DOWN);
              cout << "售价 800";
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
              //定位要打印的 地方
              CUtils::gotoXY(tmpPos.getX() + i, (tmpPos.getY() + j) * 2);

              if (i == 0 || i == 5 || j == 0 || j == 15)
              {
                  CUtils::setColor(64);
                  cout << "◆";
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
              cout << "□";

          }
      }
  }

  void CBagScene::renderLine()
  {
      //确定位置
      CPosition tmpPos;
      tmpPos.setX(describePoint.getX());
      tmpPos.setY(basePos.getY());

      CUtils::gotoXY(tmpPos);

      //确定边框颜色
      CUtils::setColor(ColorOfBorder);

      for (int i = 0; i < statePoint.getY() - 1; i++)
      {
          cout << "◆";
      }

      CUtils::setColor();
  }

  void CBagScene::renderRedShop()
  {
      CPosition tmpPos = basePos + CPosition(1, 1);

      //确定颜色
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 2));
      cout << "商店";

      CUtils::setColor();
  }

  void CBagScene::renderRedAttribute()
  {
      CPosition tmpPos = basePos + CPosition(1, 6);

      //确定颜色
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 7));
      cout << "属性";

      CUtils::setColor();
  }

  int CBagScene::choiceTask()
  {
      //清空场景
      system("cls");

      //打印边框
      renderBorder();

      //打印帮助信息
      renderHelpInfo();

      //任务红色表示
      renderRedTask();

      //打印背景边框
      renderTaskBackground();

      //打印任务信息
      renderTaskInfo();


      //切换选项卡/退出
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

      //确定颜色
      CUtils::setColor(79);
      for (int i = 0; i < 3; i++)
      {
          CUtils::gotoXY(tmpPos);
          cout << "        ";

          tmpPos = tmpPos + DI_DOWN;
      }

      CUtils::setColor(79);
      CUtils::gotoXY(basePos + CPosition(2, 12));
      cout << "任务";

      CUtils::setColor();
  }

  void CBagScene::renderTaskInfo()
  {
      //设定打印基准点
      CPosition stratPos = scenePoint + CPosition(0,-2);

      //设定打印颜色
      CUtils::setColor(142);

      //获取任务列表
      auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();

      //记录任务数量
      int countTask = 0;

      for (auto element : (*tmpTaskList))
      {
          CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 2) * 2);
          cout << element->name;

          if (element->taskType != TT_FindNPC)
          {
              CUtils::gotoXY(stratPos.getX() + 1 + countTask * 7, (stratPos.getY() + 8) * 2);
              cout << "任务要求：  ";
              if (element->itemID != ID_None)
              {
                  switch (element->itemID)
                  {
                  case ID_Apple:{cout << " 找苹果 "; break; }
                  default:  break;
                  }
                  CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 8) * 2);
                  cout << "  数量：    " << element->itemCount << "/" << element->itemMax  << endl;
              }
              else if (element->monsterID != MI_NONE)
              {
                  switch (element->monsterID)
                  {
                  case MI_DOG:{cout << "杀野狗 "; break;}
                  case MI_PIG:{cout << "杀野猪 ";break;}
                  case MI_Devil:{cout << "杀野鬼 "; break; }
                  default:  break;
                  }
                  CUtils::gotoXY(stratPos.getX() + 2 + countTask * 7, (stratPos.getY() + 8) * 2);
                  cout << "  数量：    " << element->monsterCount << "/" << element->monsterMax <<  endl;
              }
          }
          

          CUtils::gotoXY(stratPos.getX() + 3 + countTask * 7, (stratPos.getY() + 8) * 2);
          cout << "完成状态：  ";

          if (element->taskMode == MODEUNFINISED)
          {
              cout << "未完成";
          }
          else if (element->taskMode == MODEFINISED)
          {
              cout << "已完成";
          }

          CUtils::gotoXY(stratPos.getX() + 4 + countTask * 7, (stratPos.getY() + 8) * 2);
          cout << "目标 NPC：  ";

          switch (element->regainNpcID)
          {
          case SN_JIA:{cout << "找 甲 还任务"; break; }
          case SN_YI:{cout << "找 乙 还任务"; break; }
          default:  break;
          }

          //增加任务数
          countTask++;
      }

      CUtils::setColor();
  }

  void CBagScene::renderTaskBackground()
  {
      //设定打印基准点
      CPosition stratPos = scenePoint+DI_LEFT;

      //打印底色
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
          cout << "空";
      }

      CUtils::setColor();
  }
