
#include "CSceneDirector.h"
#include "CQiuDao.h"
#include "CYaHui.h"

#include "CBagScene.h"
#include "CTaskDirector.h"

void main()
{
    srand((unsigned)time(0));
    CUtils::hideCursorDisplay();

    //设置控制台的标题
    SetConsoleTitle(TEXT("武汉光谷软件校区-G0831804-CXMK81005-《寻仙记》-钟宝"));

    //设置控制台的宽高 -- 游戏分辨率
    system("mode con cols=130 lines=40");  //<200  ； <60  ; 不要空格

    CSceneDirector GO;
    GO.startGame();

    //CBagScene test;
    //test.enterUIScene();



    //auto tmpRole1 = CQiuDao::getInstance();
    //if (tmpRole1)
    //{
    //    delete tmpRole1;
    //    tmpRole1 = 0;
    //}

    //auto tmpRole2 = CYaHui::getInstance();
    //if (tmpRole2)
    //{
    //    delete tmpRole2;
    //    tmpRole2 = 0;
    //}


}