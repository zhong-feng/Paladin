#pragma once
#include "CPosition.h"

class CPosition;

class CUtils
{
public:
    // pos 位置输出 逐字输出剧情 
    static void printPerWord(CPosition pos, char *str);

	// pos 位置输出 str，然后清除
    static void printStringOnPos(CPosition pos, string str);

	//控制台光标移动函数  pos (y坐标已 *2 )
    static void gotoXY(CPosition pos);

    //控制台光标移动函数 x 行，y 列
    static void gotoXY(int x, int y);

    //控制台隐藏光标显示 
    static void hideCursorDisplay();

    //设置控制台文本颜色
    static void setColor(unsigned short GroundColor = 7);

    //移动选择光标(上下 移动  ENTER 确认)
    static void moveSelectedUpOrDown(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //sndPlaySound 用于播放背景音乐
    static void playAsyncMusicRepeatedly(string filePath)
    {
        //关闭音乐
        sndPlaySound(NULL, SND_PURGE);

        //窄宽字符转换
#ifdef UNICODE
        wstring tmpFilePath = AnsiToUnicode(filePath);
#else
        string tmpFilePath = filePath;
#endif
        //异步重复播放音乐
        sndPlaySound(tmpFilePath.c_str(), SND_ASYNC | SND_LOOP); //异步播放
    }

    //mciSendString 用于播放音效，需注意：文件名不能有空格。 路径名最好不带中文且不能过长 
    static void playSyncSoundEffect(string filePath)
    {
        //关闭音乐
        mciSendString(TEXT("stop effect"), NULL, 0, NULL);
        mciSendString(TEXT("close effect"), NULL, 0, NULL);

        ///播放音乐
        //窄宽字符转换
        //字符串格式化
        char buffer[1024] = { 0 };
        sprintf_s(buffer, "open %s alias effect", filePath.c_str());

#ifdef UNICODE
        wstring playSoundCmd = AnsiToUnicode(buffer);
#else
        string playSoundCmd = filePath;
#endif
        mciSendString(playSoundCmd.c_str(), NULL, 0, NULL);
        mciSendString(TEXT("play effect"), NULL, 0, NULL);    //同步播放
    }


private:  //2
    static std::string UnicodeToAnsi(wstring _wStr)
    {
        //---------- 将宽字符转换成窄字符 ----------
        int len = WideCharToMultiByte(CP_ACP, 0, _wStr.c_str(), -1, NULL, 0, NULL, NULL);

        char* pStr = new char[len + 1];
        memset(pStr, 0, sizeof(char)*(len + 1));

        WideCharToMultiByte(CP_ACP, 0, _wStr.c_str(), -1, pStr, len, NULL, NULL);
        //-------------------------------------------

        return string(pStr);
    }

    static std::wstring AnsiToUnicode(string _str)
    {
        //---------- 将窄字符转换成宽字符 ----------
        int len = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, NULL, 0);

        wchar_t* w_pStr = new wchar_t[len + 1];
        memset(w_pStr, 0, sizeof(wchar_t)*(len + 1));

        MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, w_pStr, len);
        //-------------------------------------------

        return wstring(w_pStr);
    }



protected:
    //上移 选择光标
    static void moveUp(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //下移 选择光标
    static void moveDown(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //擦除选择光标
    static void eraserSelect(CPosition _pos, int backgroundColour);

    //渲染选择光标
    static void renderSelect(CPosition _pos, int foregroundColor);

};


