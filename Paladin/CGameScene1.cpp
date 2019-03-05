#include "CGameScene1.h"

#include "CMonsterFactory.h"
#include "CFightDirector.h"

#include "CBagScene.h"


int CGameScene1::arrayFog[COLOFGAMESCENE1][ROWOFGAMESCENE1] = { 0 };

bool CGameScene1::devilIsDead = false;


void CGameScene1::freeMonsterList()
{
    auto itr = m_MonsterList.begin();

    while (itr != m_MonsterList.end())
    {
        if (*itr)
        {
            delete (*itr);
            *itr = 0;

            m_MonsterList.pop_front();
            itr = m_MonsterList.begin();
        }
    }
}



void CGameScene1::initPropsOnSceneArray()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //配置传送点
            if (ppSceneArray[i][j] == G1_ToScene2)
            {
                toScene2Pos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_ToScene3)
            {
                toScene3Pos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_ToBirth)
            {
                toBirthPos = CPosition(i, j);

                continue;
            }

            if (ppSceneArray[i][j] == G1_Devil)
            {
                if (devilIsDead)
                {
                    ppSceneArray[i][j] = G1_Path;
                    ppSceneArray[i][j+1] = G1_Path;

                    devilPos = CPosition(999, 999);
                }
                else
                {
                    devilPos = CPosition(i, j);
                }

                continue;
            }

            if (ppSceneArray[i][j] == G1_Pig)
            {
                auto pTmpMonster = CMonsterFactory::createMonster((CMonsterID)G1_Pig);
                pTmpMonster->setCurPos(CPosition(i, j));
                pTmpMonster->setPrePos(CPosition(i, j));

                m_MonsterList.push_back(pTmpMonster);

                ppSceneArray[i][j] = G1_Path;
                continue;
            }

            if (ppSceneArray[i][j] == G1_Dog)
            {
                auto pTmpMonster = CMonsterFactory::createMonster((CMonsterID)G1_Dog);
                pTmpMonster->setCurPos(CPosition(i, j));
                pTmpMonster->setPrePos(CPosition(i, j));

                m_MonsterList.push_back(pTmpMonster);

                ppSceneArray[i][j] = G1_Path;
                continue;
            }
        }

    }//end for i


}

bool CGameScene1::breakFog()
{
    //玩家必须有位置
    if (player.getPos().getX() == 0 || player.getPos().getY() == 0)
    {
        return false;
    }

    for (int i = player.getPos().getX() - canLook; i < player.getPos().getX() + canLook; i++)
    {
        for (int j = player.getPos().getY() - canLook; j < player.getPos().getY() + canLook; j++)
        {
            if (i >= 0 && i < COLOFGAMESCENE1 && j >= 0 && j < ROWOFGAMESCENE1)
            {
                if (CPosition(i, j) - player.getPos() <= canLook)
                {
                    arrayFog[i][j] = 1;
                }
            }
        }
    }

    return true;
}

//破除所有的迷雾

 void CGameScene1::breakAllFog()
{
    for (int i =0 ; i < height; i++)
    {
        for (int j = 0; j <width; j++)
        {
            arrayFog[i][j] = 1;

        }
    }
}

void CGameScene1::renderSceneUI()
{
    //根据人物的坐标破除迷雾
    if (!breakFog())
    {
        return;
    }

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

            //迷雾遮住 打印空白
            if (arrayFog[basePos.getX() + i][basePos.getY() + j] == 0)
            {
                CUtils::setColor();
                cout << "  ";

                continue;
            }

            //根据  时间 刷新河流状态
            static DWORD dwPreTime = GetTickCount();
             DWORD dwCurTime = GetTickCount();
             if (dwCurTime - dwPreTime > 1000)
             {
                 dwPreTime = GetTickCount();
                 flagRiver = (!flagRiver);
             }

            //映射地图相应区域
            switch (ppSceneArray[basePos.getX() + i][basePos.getY() + j])
            {
            case G1_Dog:
            case G1_Pig:
            case G1_HideBx:
            case G1_Path: { CUtils::setColor(103); cout << "  "; break; }
            case G1_Tree: { CUtils::setColor(42); cout << "树"; break; }
            case G1_River: { CUtils::setColor(23); cout << "  "; break; }
            case G1_Ripple1:
            {
                CUtils::setColor(23);
                if (flagRiver)
                {
                    cout << "  ";
                }
                else
                {
                    cout << "~~";
                }
                break; 
            }
            case G1_Ripple2: 
            { 
                CUtils::setColor(23); 
                if (flagRiver)
                {
                    cout << "~~";
                }
                else
                {
                    cout << "  ";
                }
                break; 
            }
            case G1_Bridge: { CUtils::setColor(103); cout << "█"; break; }
            case G1_ShoalWater: { CUtils::setColor(23); cout << "  "; break; }
            case G1_SmallBox: { CUtils::setColor(111); cout << "箱"; break; }
            case G1_BigBox: { CUtils::setColor(108); cout << "箱"; break; }

            case G1_DevilT: { CUtils::setColor(192); cout << "鬼"; break; }
            case G1_Devil: { CUtils::setColor(192); cout << "野"; break; }
            case G1_ToScene2:
            case G1_ToScene3:
            case G1_ToBirth: { CUtils::setColor(140); cout << "○"; break; }
            default: break;
            }

        }
    }

    //将颜色改回默认
    CUtils::setColor();
}

void CGameScene1::renderAllTheMonster()
{
    for (auto element : m_MonsterList)
    {
        //获取怪物当前坐标
        auto tmpPos = element->getCurPos();

        //确定在屏幕范围内
        int tmpX = tmpPos.getX() - basePos.getX();
        int tmpY = tmpPos.getY() - basePos.getY();

        if (tmpX > 0 && tmpX < COLOFSCENE && tmpY > 0 && tmpY < ROWOFSCENE)
        {
            //没有被迷雾遮住
            if (arrayFog[tmpPos.getX()][tmpPos.getY()] == 1)
            {
                CUtils::gotoXY(CPosition(tmpX, tmpY) + scenePoint);
                CUtils::setColor(108);
                element->renderMyself();
            }
        }
    }
}

void CGameScene1::moveAllTheMonster()
{
    for (auto element : m_MonsterList)
    {

        element->moveMyself(ppSceneArray);
    }
}

int CGameScene1::enterUIScene()
{
    //播放场景背景音乐
    CUtils::playAsyncMusicRepeatedly(".\\Resource\\Sound\\Music\\gameSence1.wav");

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

            case '0': {breakAllFog(); break; }//后门 破除所迷雾

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

            //空地 桥 浅水 可以直接走走
            if (value == G1_Path || value == G1_ShoalWater || value == G1_Bridge)
            {
                player.setPos(nextPos);
                player.setDirection(nextDirection);
            }

            if (value == G1_ToScene2 || value == G1_ToScene3 || value == G1_ToBirth)
            {
                //音效
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\transfer.wma");

                return value;
            }

            // 小宝箱 隐藏宝箱 50% 概率掉物品
            if (value == G1_SmallBox || value == G1_HideBx)
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

            if (value == G1_BigBox)
            {
                //开了宝箱后 宝箱消失
                setValueOfSceneArrayOnPos(nextPos, G1_Path);

                //掉落物品
                dropItem();

                //音效
                CUtils::playSyncSoundEffect(".\\Resource\\Sound\\Effect\\openBox.wma");
            }

            //碰到 野鬼 战斗
            if (nextPos - devilPos < 3)
            {
                if (isWinOfFightWithMonster(MI_Devil))
                {
                    //胜利 删除魔鬼信息
                    setValueOfSceneArrayOnPos(devilPos, G1_Path);
                    setValueOfSceneArrayOnPos(devilPos + DI_RIGHT, G1_Path);

                    devilIsDead = true;
                    devilPos = CPosition(999, 999);//认为不会再碰到

                }
            }


        } //end if ((_kbhit()))

        //擦除旧的事件信息
        eraserMessage();

        //怪物巡逻逻
        moveAllTheMonster();

        //与 怪物 碰撞
        touchMonster();

        //打印 场景
        renderSceneUI();

        //打印怪物
        renderAllTheMonster();

        //打印玩家
        rendScenePlayer();
    }

    return -1;
}

CGameScene1::~CGameScene1()
{
    //手动释放数据
    freeMonsterList();
}

CGameScene1::CGameScene1()
{
    toScene2Pos = CPosition(0, 0);
    toScene3Pos = CPosition(0, 0);
    toBirthPos = CPosition(0, 0);

    devilPos = CPosition(0, 0);

    canLook = DISTANCE;

    flagRiver = true;

    //确定长宽
    height = COLOFGAMESCENE1;
    width = ROWOFGAMESCENE1;

    sceneID = SI_GameScene1;
    name = "郊外";

    //动态分配 场景 地图
    ppSceneArray = new int*[height];
    memset(ppSceneArray, 0, height * sizeof(int*));

    for (int i = 0; i < height; i++)
    {
        ppSceneArray[i] = new int[width]();
    }

    //根据txt文件初始化场景数组
    initUISceneArrayOnTextFile("GameScene1");

    //从场景数组读取配置信息
    initPropsOnSceneArray();
}

void CGameScene1::touchMonster()
{
    for (auto itrMonsyer = m_MonsterList.begin();
        itrMonsyer != m_MonsterList.end(); )
    {
        if ((*itrMonsyer)->getCurPos() - player.getPos() < 3)
        {
            if (isWinOfFightWithMonster((*itrMonsyer)->getMonsterID()))
            {
                // 删除怪物
                delete (*itrMonsyer);
                *itrMonsyer = 0;

                m_MonsterList.erase(itrMonsyer);

                //迭代器失效
                itrMonsyer = m_MonsterList.begin();

                continue;
            }
            else
            {
                return;
            }
 
        }

        itrMonsyer++;
    }
}

bool CGameScene1::isWinOfFightWithMonster(CMonsterID _ID)
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

    //打印怪物
    renderAllTheMonster();

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
        player.setPos(toBirthPos);
        player.setDirection(DI_RIGHT);

        if (CYaHui::getInstance()->getIsShow())
        {
            CYaHui::getInstance()->setCurHP(1);
        }

        CQiuDao::getInstance()->setCurHP(1);

        return false;
    }
}



