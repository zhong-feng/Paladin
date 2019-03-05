#include "CBirthScene.h"
#include "CBagScene.h"
#include "CYaHui.h"
#include "CTaskDirector.h"

bool CBirthScene::isFirstToBirthscene = true;
int CBirthScene::countKillDog = -1;

CBirthScene::CBirthScene()
{
    //给自己 场景 的特殊点赋初值
    birthPos = CPosition(0, 0);
    NPCYaHuiPos = CPosition(0, 0);
    NPCShopPos = CPosition(0, 0);
    toScene1pPos = CPosition(0, 0);

    sceneID = SI_BirthScene;
    name = "新手村";

    //确定长宽
    height = COLOFBIRTHSCENE;
    width = ROWOFBIRTHSCENE;

    //动态分配 场景 地图
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height*sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //根据txt文件初始化场景数组
    initUISceneArrayOnTextFile("BirthScene");

    //从场景数组读取配置信息
    initPropsOnSceneArray();
}

void CBirthScene::renderSceneUI()
{
    //根据玩家位置确定打印基准点
    if (!setBasePosByBirthPos())
    {
        return;
    }

    for (size_t i = 0; i < COLOFSCENE; i++)
    {
        for (size_t j = 0; j < ROWOFSCENE; j++)
        {
            //确定打印位置
            CUtils::gotoXY(scenePoint.getX() + i, (scenePoint.getY() + j) * 2);

            //映射地图相应区域
            switch (ppSceneArray[basePos.getX() + i][basePos.getY() + j])
            {
            case BI_PATH:    { CUtils::setColor(63); cout << "  "; break; }
            case BI_BORDER:  { CUtils::setColor(204); cout << "█"; break; }
            case BI_TREE:    { CUtils::setColor(32); cout << "树"; break; }
            case BI_FENCE:   { CUtils::setColor(244); cout << "▓"; break; }
            case BI_WINDOW:  { CUtils::setColor(240); cout << "田"; break; }
            case BI_WALL:    { CUtils::setColor(15); cout << "█"; break; }
            case BI_PASS:    {  break; }
            case BI_ROOF1:   { CUtils::setColor(63); cout << "◢"; break; }
            case BI_ROOF2:   { CUtils::setColor(63); cout << "◣"; break; }
            case BI_ROOF3:   { CUtils::setColor(63); cout << "◥"; break; }
            case BI_ROOF4:   { CUtils::setColor(63); cout << "◤"; break; }

            case BI_BED:     { CUtils::setColor(124); cout << "□"; break; }
            case BI_SARK:    { CUtils::setColor(124); cout << "◇"; break; }

            case BI_YAHUI:    { CUtils::setColor(15); cout << "灵"; break; }
            case BI_YAHUIPASS:    { CUtils::setColor(15); cout << "心"; break; }

            case BI_SHOP: { CUtils::setColor(15); cout << "商"; break; }
            case BI_SHOPPASS: { CUtils::setColor(15); cout << "店"; break; }

            case BI_JIA:    { CUtils::setColor(15); cout << "甲"; break; }
            case BI_YI:    { CUtils::setColor(15); cout << "乙"; break; }

            case BI_BIRTH:   { CUtils::setColor(63); cout << "  "; break; }
            case BI_TOSCENE1:{  CUtils::setColor(63); cout << "○"; break; }
            default:break;
            }
        }
    }

    //将颜色改回默认
    CUtils::setColor();
}

void CBirthScene::initPropsOnSceneArray()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //确定人物出生点
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

//开场剧情

 void CBirthScene::renderStory()
{
    CPosition tmpPos = scenePoint+CPosition(1,2);

    CUtils::setColor(12);

    char str[] = "又是在做梦吗.......#为什么我会又梦到那地方#为什么梦又会那么真实###这是第多少次了#  越来越频繁了#    我知道#      我必须要去那个地方了#        那个我梦中仙境#          我要找到答案##踏上寻仙之旅";
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

          char* pTmpChar = "马上就要走了，走之前去看看 灵心 ";

          renderMessage(pTmpChar);

          _getch();
      }

 }

   void CBirthScene::renderFindYaHui()
  {
       static DWORD dwPreTime = 0; 
       DWORD dwCurTime = GetTickCount();

       //短期内不会重复触发
       if (dwCurTime - dwPreTime > 100000)
       {
           dwPreTime = GetTickCount();

           static bool isFirst = true;

           if (isFirst)
           {
               isFirst = false;

               char* pTmpChar = "求仙： 我决定了，我要离开！#谢谢你这么多年对我的照顾";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "灵心：你要去哪？";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "求仙： 梦中的地方，那个我必须要去的地方";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "灵心： 我就知道这一天会来的#我一直准备着#带上我吧！";
               renderMessage(pTmpChar);
               _getch();

               pTmpChar = "求仙：好吧#你一个人我也不放心";
               renderMessage(pTmpChar);
               _getch();

               renderMessage("灵心加入队伍");

               CYaHui::getInstance()->setIsShow(true);

               ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY()] = BI_WALL;
               ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY() + 1] = BI_WALL;

           }
           else
           {
               if (CYaHui::getInstance()->getIsShow())
               {
                   char* pTmpChar = "灵心：我先回家休息一下#走的时候记得叫我";
                   renderMessage(pTmpChar);
                   _getch();

                   renderMessage("灵心离开队伍");

                   CYaHui::getInstance()->setIsShow(false);

                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY()] = BI_YAHUI;
                   ppSceneArray[NPCYaHuiPos.getX()][NPCYaHuiPos.getY() + 1] = BI_YAHUIPASS;

               }
               else
               {
                   char* pTmpChar = "灵心：来了 来了#出来了";
                   renderMessage(pTmpChar);
                   _getch();

                   renderMessage("灵心加入队伍");

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
    //播放场景背景音乐
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\birth.wav");

    //清空渲染
    system("cls");

    //打印 边框
    renderBoder();

    //第一次进入场景，过剧情
    if (isFirstToBirthscene)
    {
        renderStory();

        isFirstToBirthscene = false;
    }

    //打印帮助信息
    renderHelpInfo();

    //打印 场景
    renderSceneUI();

    //打印玩家
    rendScenePlayer();

    //提示去找灵心
    renderMessage1();

    while (true)
    {
        //
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

            case 27:{ return -1; break; }
            default: break;
            }

            int value = getValueOfSceneArrayOnPos(nextPos);

            //路可以走
            if (value == BI_PATH)
            {
                player.setPos(nextPos);
                player.setDirection(nextDirection);
            }

            //触发 雅惠的 任务
            if (nextPos- NPCYaHuiPos<3)
            {
                renderFindYaHui();
            }

            //触发任务，收集金苹果
            if (value == BI_JIA)
            {
                renderFindJia();
            }

            //触发任务 杀狗
            if (value == BI_YI)
            {
                renderFindYi();
            }

            if (value == BI_TOSCENE1)
            {
                //音效
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                return value;
            }

            //打印 场景
            renderSceneUI();

            //打印玩家
            rendScenePlayer();

            eraserMessage();

        } //end if ((_kbhit()))
    }

    return -1;
}

void CBirthScene::renderFindJia()
{
    static bool isFirst = true;

    //确认接任还是还任务
    if (isFirst)
    {
        //已接任务数量没有到最大值
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
            char* pTmpChar = "先把手上的事做完再来吧！";
            renderMessage(pTmpChar);
            _getch();
        }

    }
    else
    {
        //循环遍历任务 链表 
        auto tmpTaskList= CTaskDirector::getInstance()->getTaskList();
        for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
        {
            if ((*itr)->regainNpcID == SN_JIA)
            {
                int res = (*itr)->enterTask(SN_JIA, describePoint + CPosition(1, 1));

                //任务完成 将其从链表中删除
                if (res == MODESUBMITED)       
                {
                    //销毁数据 
                    delete (*itr);
                    (*itr) = 0;

                    (*tmpTaskList).erase(itr); //从列表中中删除（迭代器失效）

                    isFirst = true;  //可重复接取任务

                }

                return;
            }
        }//end  for 

        //链表中 没有 相关任务 
        char* pTmpChar = "今天天气不错啊！";
        renderMessage(pTmpChar);
        _getch();
    }

    //if (isFirst)
    //{
    //    isFirst = false;

    //    char* pTmpChar = "甲： 你可以帮我帮我找 10 个苹果吗？";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "求仙： 没问题，交给我了";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "接受任务  寻找 10 个苹果";
    //    renderMessage(pTmpChar);
    //    _getch();
    //}
    //else
    //{
    //    //查看背包中 苹果的数量
    //    auto tmpBagDirector = CBagDirector::getInstance();

    //    int tmpNum = tmpBagDirector->getBag()->getCountItemID(ID_Apple);

    //    if (tmpNum >= 10)
    //    {
    //        //完成任务（可以重复接取任务）
    //        isFirst = true;

    //        //给钱   1000
    //        tmpBagDirector->setMoney(tmpBagDirector->getMoney() + 1000);

    //        //给装备
    //        tmpBagDirector->getBag()->addItem(ID_Ioricae);

    //        char* pTmpChar = "完成 找苹果 任务#获得金钱 1000#获得物品  铠甲";
    //        renderMessage(pTmpChar);
    //        _getch();

    //    }
    //    else
    //    {
    //        char* pTmpChar = "数量不够啊，再找找吧！";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //}

}

void CBirthScene::renderFindYi()
{
    static bool isFirst = true;

    //确认接任还是还任务
    if (isFirst)
    {
        //已接任务数量没有到最大值
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
            char* pTmpChar = "先把手上的事做完再来吧！";
            renderMessage(pTmpChar);
            _getch();
        }

    }
    else
    {
        //循环遍历任务 链表 
        auto tmpTaskList = CTaskDirector::getInstance()->getTaskList();
        for (auto itr = (*tmpTaskList).begin(); itr != (*tmpTaskList).end(); itr++)
        {
            if ((*itr)->regainNpcID == SN_YI)
            {
                int res = (*itr)->enterTask(SN_YI, describePoint + CPosition(1, 1));

                //任务完成 将其从链表中删除
                if (res == MODESUBMITED)
                {
                    //销毁数据
                    delete (*itr);
                    (*itr) = 0;

                    (*tmpTaskList).erase(itr); //从列表中中删除（迭代器失效）

                }

                return;
            }
        }//end  for 

        //链表中 没有 相关任务 
        char* pTmpChar = "这些天野狗好像变少了些啊！";
        renderMessage(pTmpChar);
        _getch();
    }


    //if (isFirst)
    //{
    //    isFirst = false;
    //    countKillDog = 0;

    //    char* pTmpChar = "乙： 郊外的野狗太多了#经常伤人#你可以帮我除掉一些吗？";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "求仙： 没问题，交给我了";
    //    renderMessage(pTmpChar);
    //    _getch();

    //     pTmpChar = "接受任务  杀死 10 只野狗";
    //    renderMessage(pTmpChar);
    //    _getch();

    //}
    //else
    //{
    //    if (countKillDog >= 10 && countKillDog<30)
    //    {
    //        //完成任务（不可以重复接取任务）
    //        countKillDog = 40;

    //        auto tmpBagDirector = CBagDirector::getInstance();

    //        //给钱   1000
    //        tmpBagDirector->setMoney(tmpBagDirector->getMoney() + 1000);

    //        //给装备
    //        tmpBagDirector->getBag()->addItem(ID_Sword);

    //        char* pTmpChar = "完成 找苹果 任务#获得金钱 1000#获得物品  铁剑";
    //        renderMessage(pTmpChar);
    //        _getch();

    //    }
    //    else if (countKillDog > 30)
    //    {
    //        char* pTmpChar = "上次你杀了一些狗后好多了#谢谢你啊";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //    else
    //    {
    //        char* pTmpChar = "是不是杀得太少了#外面还是好多野狗啊！";
    //        renderMessage(pTmpChar);
    //        _getch();
    //    }
    //}
}

