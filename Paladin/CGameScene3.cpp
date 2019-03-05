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
    name = "�ض��ڶ���";

    //ȷ������
    height = COLOFGAMESCENE3;
    width = ROWOFGAMESCENE3;

    //��̬���� ���� ��ͼ
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height * sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //����txt�ļ���ʼ����������
    initUISceneArrayOnTextFile("GameScene3");

    //�ӳ��������ȡ������Ϣ
    initPropsOnSceneArray();
}

  CGameScene3::~CGameScene3()
 {

 }

  //��Ҫ����װ��Һͳ�������Ϸ��������

   int CGameScene3::enterUIScene()
  {
       //���ų�����������
       CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\gameSencce23.wav");

       //��ӡ �߿�
       renderBoder();

       //��ӡ������Ϣ
       renderHelpInfo();

       //��ӡ ����
       renderSceneUI();

       //��ӡ���
       rendScenePlayer();

       while (true)
       {
           //�����û�����
           if (_kbhit())
           {
               //���������ȷ��Ŀ�� ��Ϣ
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

               case '0':{canLook = 99; break; }//һ������

               case 'm':
               case 'M':  //��������ϵͳ
               {
                   CBagScene bagSystem;
                   bagSystem.enterUIScene();

                   //�����Ⱦ
                   system("cls");

                   //��ӡ �߿�
                   renderBoder();

                   //��ӡ������Ϣ
                   renderHelpInfo();
                   break;
               }

               case 27: { return -1; break; }

               default: break;
               }

               int value = getValueOfSceneArrayOnPos(nextPos);

               //�յ� ����ֱ������
               if (value == G3_Path)
               {
                   player.setPos(nextPos);
                   player.setDirection(nextDirection);

                   //�봫�͵㰲ȫ�����������
                   if (nextPos - toScene1Pos > safetyArea && nextPos - toScene2Pos > safetyArea)
                   {
                       // 5% ��������
                       if ((rand()*rand() + rand()) % 100 < 5)
                       {
                           isWinOfFightWithMonster(MI_PIG);
                       }
                   }
               }

               if (value == G3_ToScene2 || value == G3_ToScene1)
               {
                   //��Ч
                   CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                   return value;
               }

               // С���� ���ر��� 50% ���ʵ���Ʒ
               if (value == G3_SmallBox || value == G3_HideBx)
               {
                   //���˱���� ������ʧ
                   setValueOfSceneArrayOnPos(nextPos, G1_Path);

                   if ((rand() + rand()*rand()) % 100 > 50)
                   {
                       //������Ʒ
                       dropItem();
                   }
                   else
                   {
                       renderMessage("������һ������#���ź���������ʲô��û��");
                   }

                   //��Ч
                   CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\openBox.wma");
               }

               if (value == G3_Dog || value == G3_Pig)
               {
                   if (isWinOfFightWithMonster((CMonsterID)value))
                   {
                       // ʤ���������ʧ
                       setValueOfSceneArrayOnPos(nextPos, G1_Path);

                   }
               }

           } //end if ((_kbhit()))

             //�����ɵ��¼���Ϣ
           eraserMessage();

           //��ӡ ����
           renderSceneUI();

           //��ӡ���
           rendScenePlayer();
       }


       return -1;
  }

   //�͹���ս��

    bool CGameScene3::isWinOfFightWithMonster(CMonsterID _ID)
   {
        //����ս��
        int res = CFightDirector::getInstance()->startFight(_ID);

        system("cls");

        //��ӡ �߿�
        renderBoder();

        //��ӡ������Ϣ
        renderHelpInfo();

        //��ӡ ����
        renderSceneUI();

        //��ӡ���
        rendScenePlayer();

        if (res == 1) //ս��ʤ��
        {
            //�Ӿ��� ����
            if (CYaHui::getInstance()->getIsShow())
            {
                CYaHui::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
                CYaHui::getInstance()->levelUp();
            }

            CQiuDao::getInstance()->setCurEXP(CQiuDao::getInstance()->getCurEXP() + 100);
            CQiuDao::getInstance()->levelUp();

            //��ӡʤ����Ϣ
            renderMessage("��ϲ�㣡ս��ʤ��#��þ��� 100");

            _getch();

            //������Ʒ
            dropItem();

            return true;
        }
        else  //ս��ʧ��
        {
            //ǿ�Ʊ�Ϊһ��Ѫ���ص���ͼ������
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

    //�ӳ��������ȡ����

     void CGameScene3::initPropsOnSceneArray()
    {
         for (int i = 0; i < height; i++)
         {
             for (int j = 0; j < width; j++)
             {
                 //���ô��͵�
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

     //������ӡ����

      void CGameScene3::renderSceneUI()
     {
          for (size_t i = 0; i < COLOFSCENE; i++)
          {
              for (size_t j = 0; j < ROWOFSCENE; j++)
              {
                  //ȷ����ӡλ��
                  CUtils::gotoXY(scenePoint.getX() + i, (scenePoint.getY() + j) * 2);

                  //��Ұ��Χ����Ĳ���ӡ
                  if (CPosition(i, j) - player.getPos() > canLook)
                  {
                      CUtils::setColor(0);
                      cout << "  ";

                      continue;
                  }

                  //ӳ���ͼ��Ӧ���� ppSceneArray[basePos.getX() + i][basePos.getY() + j]
                  switch (ppSceneArray[i][j])
                  {
                  case G3_HideBx:
                  case G3_Path: { CUtils::setColor(103); cout << "  "; break; }
                  case G3_Border: { CUtils::setColor(127); cout << "��"; break; }
                  case G3_SmallBox: { CUtils::setColor(111); cout << "��"; break; }
                  case G3_Dog: { CUtils::setColor(78); cout << "��"; break; }
                  case G3_Pig: { CUtils::setColor(78); cout << "��"; break; }
                  case G3_ToScene2:
                  case G3_ToScene1: { CUtils::setColor(140); cout << "��"; break; }
                  default:  break;
                  }
              }
          }

          //����ɫ�Ļ�Ĭ��
          CUtils::setColor();
     }

