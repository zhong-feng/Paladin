#include "CSelectedCursor.h"


void CSelectedCursor::render(CPosition _pos)
{
    //ȷ��λ��
    CUtils::gotoXY(_pos);

    //������ɫ
    CUtils::setColor(11);

    cout << "��";

    CUtils::setColor();
}

CSelectedCursor::~CSelectedCursor()
{

}

CSelectedCursor::CSelectedCursor()
{
    pos = CPosition(0, 0);
}
