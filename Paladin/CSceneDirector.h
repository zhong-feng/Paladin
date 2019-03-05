#pragma once
#include "CSceneFactory.h"

class CSceneDirector
{
public:
    CSceneDirector()
    {
        m_Sence = CSceneFactory::createScene(CI_WELCOME);
    }
    ~CSceneDirector()
    {
        if (m_Sence)
        {
            delete m_Sence;
            m_Sence = 0;
        }
    }

    void startGame()
    {
        while (true)
        {
            auto res = m_Sence->enterUIScene();

            if (m_Sence)
            {
                delete m_Sence;
                m_Sence = nullptr;
            }

            if (res == -1)
            {
                return;
            }

            m_Sence = CSceneFactory::createScene((CSceneTransfer)res);

        }
    }

public:
    CScene * m_Sence;

};

