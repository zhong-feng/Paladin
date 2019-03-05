#include "CBirthScene.h"
#include "CBagScene.h"
#include "CYaHui.h"
#include "CTaskDirector.h"

bool CBirthScene::isFirstToBirthscene = true;
int CBirthScene::countKillDog = -1;

CBirthScene::CBirthScene()
{
    //���Լ� ���� ������㸳��ֵ
    birthPos = CPosition(0, 0);
    NPCYaHuiPos = CPosition(0, 0);
    NPCShopPos = CPosition(0, 0);
    toScene1pPos = CPosition(0, 0);

    sceneID = SI_BirthScene;
    name = "���ִ�";

    //ȷ������
    height = COLOFBIRTHSCENE;
    width = ROWOFBIRTHSCENE;

    //��̬���� ���� ��ͼ
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height*sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //����txt�ļ���ʼ����������
    initUISceneArrayOnTextFile("BirthScene");

    //�ӳ��������ȡ������Ϣ
    initPropsOnSceneArray();
}

void CBirthScene::renderSceneUI()
{
    //�������λ��ȷ����ӡ��׼��
    if (!setBasePosByBirthPos())
    {
        return;
    }

    for (size_t i = 0; i < COLOFSCENE; i++)
    {
        for (size_t j = 0; j < ROWOFSCENE; j++)
        {
            //ȷ����ӡλ��
            CUtils::gotoXY(scenePoint.getX() + i, (scenePoint.getY() + j) * 2);

            //ӳ���ͼ��Ӧ����
            switch (ppSceneArray[basePos.getX() + i][basePos.getY() + j])
            {
            case BI_PATH:    { CUtils::setColor(63); cout << "  "; break; }
            case BI_BORDER:  { CUtils::setColor(204); cout << "��"; break; }
            case BI_TREE:    { CUtils::setColor(32); cout << "��"; break; }
            case BI_FENCE:   { CUtils::setColor(244); cout << "��"; break; }
            case BI_WINDOW:  { CUtils::setColor(240); cout << "��"; break; }
            case BI_WALL:    { CUtils::setColor(15); cout << "��"; break; }
            case BI_PASS:    {  break; }
            case BI_ROOF1:   { CUtils::setColor(63); cout << "��"; break; }
            case BI_ROOF2:   { CUtils::setColor(63); cout << "��"; break; }
            case BI_ROOF3:   { CUtils::setColor(63); cout << "��"; break; }
            case BI_ROOF4:   { CUtils::setColor(63); cout << "��"; break; }

            case BI_BED:     { CUtils::setColor(124); cout << "��"; break; }
            case BI_SARK:    { CUtils::setColor(124); cout << "��"; break; }

            case BI_YAHUI:    { CUtils::setColor(15); cout << "��"; break; }
            case BI_YAHUIPASS:    { CUtils::setColor(15); cout << "��"; break; }

            case BI_SHOP: { CUtils::setColor(15); cout << "��"; break; }
            case BI_SHOPPASS: { CUtils::setColor(15); cout << "��"; break; }

            case BI_JIA:    { CUtils::setColor(15); cout << "��"; break; }
            case BI_YI:    { CUtils::setColor(15); cout << "��"; break; }

            case BI_BIRTH:   { CUtils::setColor(63); cout << "  "; break; }
            case BI_TOSCENE1:{  CUtils::setColor(63); cout << "��"; break; }
            default:break;
            }
        }
    }

    //����ɫ�Ļ�Ĭ��
    CUtils::setColor();
}

void CBirthScene::initPropsOnSceneArray()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //ȷ�����������
            if (ppSceneArray[i][j] == BI_BIRTH)
            {
                birthPos = CPosition(i, j);

                ppSceneArray[i][j] = BI_PATH;
            }

            if (ppSceneArray[i][j] == BI_YAHUI)
            {
                NPCYaHuiPos = CPosition(i, j);

                if (CYaHui::getInstance()->getIsShow())
                {
                    ppSceneArray[i][j] = BI_WALL;
                    ppSceneArray[i][j + 1] = BI_WALL;
                }
            }

            if (ppSceneArray[i][j] == BI_SHOP)
            {
                NPCShopPos = CPosition(i, j);
            }

            if (ppSceneArray[i][j] == BI_TOSCENE1)
            {
                toScene1pPos = CPosition(i, j);
            }

            if (ppSceneArray[i][j] == BI_JIA)
            {
                NPCJiaPos = CPosition(i, j);
            }

            if (ppSceneArray[i][j] == BI_YI)
            {
                NPCYiPos = CPosition(i, j);
            }


        }

    }//end for i

    if (isFirstToBirthscene)
    {
        player.setPos(birthPos);
        player.setDirection(DI_RIGHT);
    }
    else
    {
        player.setPos(toScene1pPos);
        player.setDirection(DI_LEFT);
    }
}

//��������

 void CBirthScene::renderStory()
{
    CPosition tmpPos = scenePoint+CPosition(1,2);

    CUtils::setColor(12);

    char str[] = "������������.......#Ϊʲô�һ����ε��ǵط�#Ϊʲô���ֻ���ô��ʵ###���ǵڶ��ٴ���#  Խ��ԽƵ����#    ��֪��#      �ұ���Ҫȥ�Ǹ��ط���#        �Ǹ��������ɾ�#          ��Ҫ�ҵ���##̤��Ѱ��֮��";
    CUtils::printPerWord(tmpPos, str);

    CUtils::setColor();
    _getch();

}

  void CBirthScene::renderMessage1()
 {

      static bool isFirst = true;

      if (isFirst)
      {
          isFirst = false;

          char* pTmpChar = "���Ͼ�Ҫ���ˣ���֮ǰȥ���� ���� ";

          renderMessage(pTmpChar);

          _getch();
      }

 }

   void CBirthScene::renderFindYaHui()
  {
       static DWORD dwPreTime = 0; 
       DWORD dwCurTime = GetTickCount();

       //�����ڲ����ظ�����
       if (dwCurTime - dwPreTime > 100000)
       {
           dwPreTime = GetTickCount();

           static bool isFirst = true;

           if (isFirst)
           {
               isFirst = false;

               char* pTmpChar = "���ɣ� �Ҿ����ˣ���Ҫ�뿪��#лл����ô������ҵ��չ�";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "���ģ���Ҫȥ�ģ�";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "���ɣ� ���еĵط����Ǹ��ұ���Ҫȥ�ĵط�";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "���ģ� �Ҿ�֪����һ�������#��һֱ׼����#�����Ұɣ�";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "���ɣ��ð�#��һ������Ҳ������";
               renderMessage(pTmpChar);
               _getch();

               renderMessage("���ļ������");

               CYaHui::getInstance()->setIsShow(true);

               ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY()] = BI_WALL;
               ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY() + 1] = BI_WALL;

           }
           else
           {
               if (CYaHui::getInstance()->getIsShow())
               {
                   char* pTmpChar = "���ģ����Ȼؼ���Ϣһ��#�ߵ�ʱ��ǵý���";
                   renderMessage(pTmpChar);
                   _getch();

                   renderMessage("�����뿪����");

                   CYaHui::getInstance()->setIsShow(false);

                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY()] = BI_YAHUI;
                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY() + 1] = BI_YAHUIPASS;

               }
               else
               {
                   char* pTmpChar = "���ģ����� ����#������";
                   renderMessage(pTmpChar);
                   _getch();

                   renderMessage("���ļ������");

                   CYaHui::getInstance()->setIsShow(true);

                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY()] = BI_WALL;
                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY() + 1] = BI_WALL;

               }
           }
       }
     
  }

CBirthScene::~CBirthScene()
{

}

int CBirthScene::enterUIScene()
{
    //���ų�����������
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\birth.wav");

    //�����Ⱦ
    system("cls");

    //��ӡ �߿�
    renderBoder();

    //��һ�ν��볡����������
    if (isFirstToBirthscene)
    {
        renderStory();

        isFirstToBirthscene = false;
    }

    //��ӡ������Ϣ
    renderHelpInfo();

    //��ӡ ����
    renderSceneUI();

    //��ӡ���
    rendScenePlayer();

    //��ʾȥ������
    renderMessage1();

    while (true)
    {
        //
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

            case 27:{ return -1; break; }
            default: break;
            }

            int value = getValueOfSceneArrayOnPos(nextPos);

            //·������
            if (value == BI_PATH)
            {
                player.setPos(nextPos);
                player.setDirection(nextDirection);
            }

            //���� �Żݵ� ����
            if (nextPos- NPCYaHuiPos<3)
            {
                renderFindYaHui();
            }

            //���������ռ���ƻ��
            if (value == BI_JIA)
            {
                renderFindJia();
            }

            //�������� ɱ��
            if (value == BI_YI)
            {
                renderFindYi();
            }

            if (value == BI_TOSCENE1)
            {
                //��Ч
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                return value;
            }

            //��ӡ ����
            renderSceneUI();

            //��ӡ���
            rendScenePlayer();

            eraserMessage();

        } //end if ((_kbhit()))
    }

    return -1;
}

void CBirthScene::renderFindJia()
{
    static bool isFirst = true;

    //ȷ�Ͻ��λ��ǻ�����
    if (isFirst)
    {
        //�ѽ���������û�е����ֵ
        if (CTaskDirector::getInstance()->getCountNum() < CTaskDirector::getInstance()->getMaxNum())
        {
            auto tmpTask =new CTaskBase(TI_CollectApple);

            int res = tmpTask->enterTask(SN_JIA, describePoint + CPosition(1, 1));

            if (res != MODEUNTAKE)
            {
                auto tmpTaskDirector = CTaskDirector::getInstance();

                tmpTaskDirector->getTaskList()->push_back(tmpTask);

                tmpTaskDirector->setCountNum(tmpTaskDirector->getCountNum() + 1);

                isFirst = false;
            }
        }
        else
        {
            char* pTmpChar = "�Ȱ����ϵ������������ɣ�";
            renderMessage(pTmpChar);
            _getch();
        }

    }
    else
    {
        //ѭ���������� ���� 
        auto tmpTaskList= CTaskDirector::getInstance()->getTaskList();
        for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
        {
            if ((*itr)->regainNpcID == SN_JIA)
            {
                int res = (*itr)->enterTask(SN_JIA, describePoint + CPosition(1, 1));

                //������� �����������ɾ��
                if (res == MODESUBMITED)       
                {
                    //�������� 
                    delete (*itr);
                    (*itr) = 0;

                    (*tmpTaskList).erase(itr); //���б�����ɾ����������ʧЧ��

                    isFirst = true;  //���ظ���ȡ����

                }

                return;
            }
        }//end  for 

        //������ û�� ������� 
        char* pTmpChar = "��������������";
        renderMessage(pTmpChar);
        _getch();
    }

    //if (isFirst)
    //{
    //    isFirst = false;

    //    char* pTmpChar = "�ף� ����԰��Ұ����� 10 ��ƻ����";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "���ɣ� û���⣬��������";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "��������  Ѱ�� 10 ��ƻ��";
    //    renderMessage(pTmpChar);
    //    _getch();
    //}
    //else
    //{
    //    //�鿴������ ƻ��������
    //    auto tmpBagDirector = CBagDirector::getInstance();

    //    int tmpNum = tmpBagDirector->getBag()->getCountItemID(ID_Apple);

    //    if (tmpNum >= 10)
    //    {
    //        //������񣨿����ظ���ȡ����
    //        isFirst = true;

    //        //��Ǯ   1000
    //        tmpBagDirector->setMoney(tmpBagDirector->getMoney() + 1000);

    //        //��װ��
    //        tmpBagDirector->getBag()->addItem(ID_Ioricae);

    //        char* pTmpChar = "��� ��ƻ�� ����#��ý�Ǯ 1000#�����Ʒ  ����";
    //        renderMessage(pTmpChar);
    //        _getch();

    //    }
    //    else
    //    {
    //        char* pTmpChar = "�����������������Ұɣ�";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //}

}

void CBirthScene::renderFindYi()
{
    static bool isFirst = true;

    //ȷ�Ͻ��λ��ǻ�����
    if (isFirst)
    {
        //�ѽ���������û�е����ֵ
        if (CTaskDirector::getInstance()->getCountNum() < CTaskDirector::getInstance()->getMaxNum())
        {
            auto tmpTask = new CTaskBase(TI_SikllDog);

            int res = tmpTask->enterTask(SN_YI, describePoint + CPosition(1, 1));

            if (res != MODEUNTAKE)
            {
                auto tmpTaskDirector = CTaskDirector::getInstance();

                tmpTaskDirector->getTaskList()->push_back(tmpTask);

                tmpTaskDirector->setCountNum(tmpTaskDirector->getCountNum() + 1);

                isFirst = false;
            }
        }
        else
        {
            char* pTmpChar = "�Ȱ����ϵ������������ɣ�";
            renderMessage(pTmpChar);
            _getch();
        }

    }
    else
    {
        //ѭ���������� ���� 
        auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();
        for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
        {
            if ((*itr)->regainNpcID == SN_YI)
            {
                int res = (*itr)->enterTask(SN_YI, describePoint + CPosition(1, 1));

                //������� �����������ɾ��
                if (res == MODESUBMITED)
                {
                    //��������
                    delete (*itr);
                    (*itr) = 0;

                    (*tmpTaskList).erase(itr); //���б�����ɾ����������ʧЧ��

                }

                return;
            }
        }//end  for 

        //������ û�� ������� 
        char* pTmpChar = "��Щ��Ұ�����������Щ����";
        renderMessage(pTmpChar);
        _getch();
    }


    //if (isFirst)
    //{
    //    isFirst = false;
    //    countKillDog = 0;

    //    char* pTmpChar = "�ң� �����Ұ��̫����#��������#����԰��ҳ���һЩ��";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "���ɣ� û���⣬��������";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "��������  ɱ�� 10 ֻҰ��";
    //    renderMessage(pTmpChar);
    //    _getch();

    //}
    //else
    //{
    //    if (countKillDog >= 10 && countKillDog<30)
    //    {
    //        //������񣨲������ظ���ȡ����
    //        countKillDog = 40;

    //        auto tmpBagDirector = CBagDirector::getInstance();

    //        //��Ǯ   1000
    //        tmpBagDirector->setMoney(tmpBagDirector->getMoney() + 1000);

    //        //��װ��
    //        tmpBagDirector->getBag()->addItem(ID_Sword);

    //        char* pTmpChar = "��� ��ƻ�� ����#��ý�Ǯ 1000#�����Ʒ  ����";
    //        renderMessage(pTmpChar);
    //        _getch();

    //    }
    //    else if (countKillDog > 30)
    //    {
    //        char* pTmpChar = "�ϴ���ɱ��һЩ����ö���#лл�㰡";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //    else
    //    {
    //        char* pTmpChar = "�ǲ���ɱ��̫����#���滹�Ǻö�Ұ������";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //}
}

