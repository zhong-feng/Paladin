
#include "CSceneDirector.h"
#include "CQiuDao.h"
#include "CYaHui.h"

#include "CBagScene.h"
#include "CTaskDirector.h"

void main()
{
    srand((unsigned)time(0));
    CUtils::hideCursorDisplay();

    //���ÿ���̨�ı���
    SetConsoleTitle(TEXT("�人������У��-G0831804-CXMK81005-��Ѱ�ɼǡ�-�ӱ�"));

    //���ÿ���̨�Ŀ�� -- ��Ϸ�ֱ���
    system("mode con cols=130 lines=40");  //<200  �� <60  ; ��Ҫ�ո�

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