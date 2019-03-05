#pragma once
#include "CBirthScene.h"
#include "CGameScene1.h"
#include "CGameScene2.h"
#include "CGameScene3.h"

#include "CWelcomeScene.h"

#include "CFightScene.h"


class CSceneFactory
{
public:
    static CScene* createScene(CSceneTransfer _transfer);
};

