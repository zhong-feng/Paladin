#include "CSceneFactory.h"


CScene* CSceneFactory::createScene(CSceneTransfer _transfer)
{
    CScene* tmpScene = nullptr;

    CPlayer tmpPlayer;

    switch (_transfer)
    {

    case CI_Scene1TOBirth:{ tmpScene = new CBirthScene(); break; }

    case CI_WELCOME:{ tmpScene = new CWelcomeScene(); break; }

    case CI_Scene2TOScene1:
    {
        tmpScene = new CGameScene1();

        auto tmpGameScenc1 = (CGameScene1*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc1->getToScene2Pos());
        tmpPlayer.setDirection(DI_RIGHT);

        tmpScene->setPlayer(tmpPlayer);

        break;
    }
    case CI_Scene3TOScene1:
    { 
        tmpScene = new CGameScene1();

        auto tmpGameScenc1 = (CGameScene1*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc1->getToScene3Pos());
        tmpPlayer.setDirection(DI_LEFT);

        tmpScene->setPlayer(tmpPlayer);

        break; 
    }
    case CI_BirthTOScene1:
    {
        tmpScene = new CGameScene1(); 

        auto tmpGameScenc1 = (CGameScene1*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc1->getToBirthPos());
        tmpPlayer.setDirection(DI_RIGHT);

        tmpScene->setPlayer(tmpPlayer);

        break; 
    }

    case CI_Scene3TOScene2:
    {
        tmpScene = new CGameScene2();

        auto tmpGameScenc2 = (CGameScene2*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc2->getToScene3Pos());
        tmpPlayer.setDirection(DI_RIGHT);

        tmpScene->setPlayer(tmpPlayer);

        break; 
    }
    case CI_Scene1TOScene2:
    {
        tmpScene = new CGameScene2();

        auto tmpGameScenc2 = (CGameScene2*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc2->getToScene1Pos());
        tmpPlayer.setDirection(DI_LEFT);

        tmpScene->setPlayer(tmpPlayer);
        break; 
    }

    case CI_Scene1TOScene3:
    { 
        tmpScene = new CGameScene3(); 

        auto tmpGameScenc3 = (CGameScene3*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc3->getToScene1Pos());
        tmpPlayer.setDirection(DI_RIGHT);

        tmpScene->setPlayer(tmpPlayer);

        break; 
    }
    case CI_Scene2TOScene3:
    {
        tmpScene = new CGameScene3(); 

        auto tmpGameScenc3 = (CGameScene3*)tmpScene;

        tmpPlayer.setPos(tmpGameScenc3->getToScene2Pos());
        tmpPlayer.setDirection(DI_RIGHT);

        tmpScene->setPlayer(tmpPlayer);

        break; 
    
    }

    case CI_FIGHTSCENE:{ tmpScene = new CFightScene(); break; }

    default:  break;
    }

    return tmpScene;
}
