#include "CUtils.h"


void CUtils::printStringOnPos(CPosition pos, string str)
{
    gotoXY(pos);
    cout << str;
    cout << endl;

    //��ͣ
    _getch();  //�� system("pause") ��

    gotoXY(pos);
    for (size_t i = 0; i < str.size(); i++)
    {
        cout << " ";
    }
}

void CUtils::gotoXY(CPosition pos) //x �У�y ��
{
    //ע��x��y��˳��
    COORD position = { (short)(pos.getY() * 2), short(pos.getX()) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CUtils::gotoXY(int x, int y) //x �У�y ��
{
    //ע��x��y��˳��
    COORD position = { (short)y, (short)x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}



void CUtils::hideCursorDisplay()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = false;
    SetConsoleCursorInfo(hOut, &cci);
}


void CUtils::setColor(unsigned short GroundColor /*= 7*/)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, GroundColor);
}

//�ƶ�ѡ����(���� �ƶ�  ENTER ȷ��)

 void CUtils::moveSelectedUpOrDown(int & curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor)
{
    while (true)
    {
        switch (_getch())
        {
        case 'w':
        case 'W': {moveUp(curSelect, maxNum, _pos, backgroundColour, foregroundColor); break; }
        case 's':
        case 'S': {moveDown(curSelect, maxNum, _pos, backgroundColour, foregroundColor); break; }
        case '\r': {return; break; }
        default:   break;
        }
    }
}

 //���� ѡ����

 void CUtils::moveUp(int & curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor)
 {
     //����ѡ����
     eraserSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), backgroundColour);

     curSelect--;

     if (curSelect < 0)
     {
         curSelect = maxNum-1;
     }

     //��Ⱦѡ����
     renderSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), foregroundColor);
 }

  //���� ѡ����

   void CUtils::moveDown(int & curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor)
  {
      //����ѡ����
      eraserSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), backgroundColour);

      curSelect++;

      if (curSelect >= maxNum)
      {
          curSelect = 0;
      }

      //��Ⱦѡ����
      renderSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), foregroundColor);
  }

   //����ѡ����

    void CUtils::eraserSelect(CPosition _pos, int backgroundColour)
   {
       gotoXY(_pos);
       setColor(backgroundColour);
       cout << "  " << endl;

   }

    //��Ⱦѡ����

     void CUtils::renderSelect(CPosition _pos, int foregroundColor)
    {
        gotoXY(_pos);
        setColor(foregroundColor);
        cout << "��" << endl;
    }

void CUtils::printPerWord(CPosition pos, char *str)
{
    //ȷ�� ��ʼ ���λ��
    gotoXY(pos);

    bool fast = false;

    while (*str != '\0')
    {

        if (_kbhit())
        {
            char keyCode = _getch();
            if (keyCode == '\r')
            {
                fast = true;
               
            }
        }

        //����#����
        if (*str == '#')
        {
            pos = pos + DI_DOWN;
            CUtils::gotoXY(pos);

            str++;
            continue;
        }

        cout << *str;
        str++;

        if (!fast)
        {
            Sleep(30);
        }
 
    }

    cout << endl;

}




