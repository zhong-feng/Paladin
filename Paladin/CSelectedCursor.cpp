#include "CSelectedCursor.h"


void CSelectedCursor::render(CPosition _pos)
{
    //确认位置
    CUtils::gotoXY(_pos);

    //设置颜色
    CUtils::setColor(11);

    cout << "◇";

    CUtils::setColor();
}

CSelectedCursor::~CSelectedCursor()
{

}

CSelectedCursor::CSelectedCursor()
{
    pos = CPosition(0, 0);
}
