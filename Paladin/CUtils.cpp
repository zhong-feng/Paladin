#include "CUtils.h"


void CUtils::printStringOnPos(CPosition pos, string str)
{
    gotoXY(pos);
    cout << str;
    cout << endl;

    //暂停
    _getch();  //比 system("pause") 好

    gotoXY(pos);
    for (size_t i = 0; i < str.size(); i++)
    {
        cout << " ";
    }
}

void CUtils::gotoXY(CPosition pos) //x 行，y 列
{
    //注意x和y的顺序
    COORD position = { (short)(pos.getY() * 2), short(pos.getX()) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void CUtils::gotoXY(int x, int y) //x 行，y 列
{
    //注意x和y的顺序
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

//移动选择光标(上下 移动  ENTER 确认)

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

 //上移 选择光标

 void CUtils::moveUp(int & curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor)
 {
     //擦除选择光标
     eraserSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), backgroundColour);

     curSelect--;

     if (curSelect < 0)
     {
         curSelect = maxNum-1;
     }

     //渲染选择光标
     renderSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), foregroundColor);
 }

  //下移 选择光标

   void CUtils::moveDown(int & curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor)
  {
      //擦除选择光标
      eraserSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), backgroundColour);

      curSelect++;

      if (curSelect >= maxNum)
      {
          curSelect = 0;
      }

      //渲染选择光标
      renderSelect(CPosition(_pos.getX() + curSelect, _pos.getY()), foregroundColor);
  }

   //擦除选择光标

    void CUtils::eraserSelect(CPosition _pos, int backgroundColour)
   {
       gotoXY(_pos);
       setColor(backgroundColour);
       cout << "  " << endl;

   }

    //渲染选择光标

     void CUtils::renderSelect(CPosition _pos, int foregroundColor)
    {
        gotoXY(_pos);
        setColor(foregroundColor);
        cout << "→" << endl;
    }

void CUtils::printPerWord(CPosition pos, char *str)
{
    //确认 初始 输出位置
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

        //遇到#换行
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




