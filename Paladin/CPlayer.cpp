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
    //ȷ����� ��Ⱦ ��ɫ
    CUtils::setColor(ColorOfPlayer);

    switch (direction)
    {
    case DI_UP:    {cout << "��"; break; }
    case DI_DOWN:  {cout << "��"; break; }
    case DI_RIGHT: {cout << "��"; break; }
    case DI_LEFT:  {cout << "��"; break; }
    default: break;
    }

    CUtils::setColor();
}
