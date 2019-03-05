#include "CGameScene3.h"

#include "CMonsterFactory.h"
#include "CFightDirector.h"

#include "CBagScene.h"

 CGameScene3::CGameScene3()
{
    toScene1Pos = CPosition(0, 0);
    toScene2Pos = CPosition(0, 0);


    canLook = DISTANCE;

    safetyArea = SAFETYLENGTH;

    sceneID = SI_GameScene3;
    name = "地洞第二层";

    //确定长宽
    height = COLOFGAMESCENE3;
    width = ROWOFGAMESCENE3;

    //动态分配 场景 地图
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height * sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //根据txt文件初始化场景数组
    initUISceneArrayOnTextFile("GameScene3");

    //从场景数组读取配置信息
    initPropsOnSceneArray();
}

  CGameScene3::~CGameScene3()
 {

 }

  //重要：封装玩家和场景的游戏交互过程

   int CGameScene3::enterUIScene()
  {
       //播放场景背景音乐
       CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\gameSencce23.wav");

       //打印 边框
       renderBoder();

       //打印帮助信息
       renderHelpInfo();

       //打印 场景
       renderSceneUI();

       //打印玩家
       rendScenePlayer();

       while (true)
       {
           //接受用户输入
           if (_kbhit())
           {
               //定义变量，确定目标 信息
               CPosition nextPos = player.getPos();
               CDirection nextDirection = DI_NONE;

               char keyCode = _getch();
               switch (keyCode)
               {
               case 'a':
               case 'A': {nextPos = nextPos + DI_LEFT; nextDirection = DI_LEFT; break; }
               case 'w':
               case 'W': {nextPos = nextPos + DI_UP; nextDirection = DI_UP; break; }
               case 'd':
               case 'D': {nextPos = nextPos + DI_RIGHT; nextDirection = DI_RIGHT; break; }
               case 's':
               case 'S': {nextPos = nextPos + DI_DOWN; nextDirection = DI_DOWN; break; }

               case '0':{canLook = 99; break; }//一键开灯

               case 'm':
               case 'M':  //进入属性系统
               {
                   CBagScene bagSystem;
                   bagSystem.enterUIScene();

                   //清空渲染
                   system("cls");

                   //打印 边框
                   renderBoder();

                   //打印帮助信息
                   renderHelpInfo();
                   break;
               }

               case 27: { return -1; break; }

               default: break;
               }

               int value = getValueOfSceneArrayOnPos(nextPos);

               //空地 可以直接走走
               if (value == G3_Path)
               {
                   player.setPos(nextPos);
                   player.setDirection(nextDirection);

                   //离传送点安全距离随机遇怪
                   if (nextPos - toScene1Pos > safetyArea && nextPos - toScene2Pos > safetyArea)
                   {
                       // 5% 概率遇怪
                       if ((rand()*rand() + rand()) % 100 < 5)
                       {
                           isWinOfFightWithMonster(MI_PIG);
                       }
                   }
               }

               if (value == G3_ToScene2 || value == G3_ToScene1)
               {
                   //音效
                   CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                   return value;
               }

               // 小宝箱 隐藏宝箱 50% 概率掉物品
               if (value == G3_SmallBox || value == G3_HideBx)
               {
                   //开了宝箱后 宝箱消失
                   setValueOfSceneArrayOnPos(nextPos, G1_Path);

                   if ((rand() + rand()*rand()) % 100 > 50)
                   {
                       //掉落物品
                       dropItem();
                   }
                   else
                   {
                       renderMessage("发现了一个宝箱#很遗憾，宝箱里什么都没有");
                   }

                   //音效
                   CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\openBox.wma");
               }

               if (value == G3_Dog || value == G3_Pig)
               {
                   if (isWinOfFightWithMonster((CMonsterID)value))
                   {
                       // 胜利后怪物消失
                       setValueOfSceneArrayOnPos(nextPos, G1_Path);

                   }
               }

           } //end if ((_kbhit()))

             //擦除旧的事件信息
           eraserMessage();

           //打印 场景
           renderSceneUI();

           //打印玩家
           rendScenePlayer();
       }


       return -1;
  }

   //和怪物战斗

    bool CGameScene3::isWinOfFightWithMonster(CMonsterID _ID)
   {
        //触发战斗
        int res = CFightDirector::getInstance()->startFight(_ID);

        system("cls");

        //打印 边框
        renderBoder();

        //打印帮助信息
        renderHelpInfo();

        //打印 场景
        renderSceneUI();

        //打印玩家
        rendScenePlayer();

        if (res == 1) //战斗胜利
        {
            //加经验 升级
            if (CYaHui::getInstance()->getIsShow())
            {
                CYaHui::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
                CYaHui::getInstance()->levelUp();
            }

            CQiuDao::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
            CQiuDao::getInstance()->levelUp();

            //打印胜利消息
            renderMessage("恭喜你！战斗胜利#获得经验 100");

            _getch();

            //掉落物品
            dropItem();

            return true;
        }
        else  //战斗失败
        {
            //强制变为一点血，回到地图出发点
            player.setPos(toScene2Pos);
            player.setDirection(DI_RIGHT);

            if (CYaHui::getInstance()->getIsShow())
            {
                CYaHui::getInstance()->setCurHP(1);
            }

            CQiuDao::getInstance()->setCurHP(1);

            return false;
        }
   }

    //从场景数组读取配置

     void CGameScene3::initPropsOnSceneArray()
    {
         for (int i = 0; i < height; i++)
         {
             for (int j = 0; j < width; j++)
             {
                 //配置传送点
                 if (ppSceneArray[i][j] == G3_ToScene1)
                 {
                     toScene1Pos = CPosition(i, j);

                     continue;
                 }

                 if (ppSceneArray[i][j] == G3_ToScene2)
                 {
                     toScene2Pos = CPosition(i, j);

                     continue;
                 }


             }

         }//end for i
    }

     //场景打印函数

      void CGameScene3::renderSceneUI()
     {
          for (size_t i = 0; i < COLOFSCENE; i++)
          {
              for (size_t j = 0; j < ROWOFSCENE; j++)
              {
                  //确定打印位置
                  CUtils::gotoXY(scenePoint.getX() + i, (scenePoint.getY() + j) * 2);

                  //视野范围以外的不打印
                  if (CPosition(i, j) - player.getPos() > canLook)
                  {
                      CUtils::setColor(0);
                      cout << "  ";

                      continue;
                  }

                  //映射地图相应区域 ppSceneArray[basePos.getX() + i][basePos.getY() + j]
                  switch (ppSceneArray[i][j])
                  {
                  case G3_HideBx:
                  case G3_Path: { CUtils::setColor(103); cout << "  "; break; }
                  case G3_Border: { CUtils::setColor(127); cout << "█"; break; }
                  case G3_SmallBox: { CUtils::setColor(111); cout << "箱"; break; }
                  case G3_Dog: { CUtils::setColor(78); cout << "狗"; break; }
                  case G3_Pig: { CUtils::setColor(78); cout << "猪"; break; }
                  case G3_ToScene2:
                  case G3_ToScene1: { CUtils::setColor(140); cout << "○"; break; }
                  default:  break;
                  }
              }
          }

          //将颜色改回默认
          CUtils::setColor();
     }

