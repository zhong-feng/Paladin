#include "CPlayer.h"


CPlayer::CPlayer()
{
    pos = CPosition();
    direction = DI_UP;
}

CPlayer::~CPlayer()
{

}

void CPlayer::scenePlayer()
{
    //确定玩家 渲染 颜色
    CUtils::setColor(ColorOfPlayer);

    switch (direction)
    {
    case DI_UP:    {cout << "↑"; break; }
    case DI_DOWN:  {cout << "↓"; break; }
    case DI_RIGHT: {cout << "→"; break; }
    case DI_LEFT:  {cout << "←"; break; }
    default: break;
    }

    CUtils::setColor();
}
