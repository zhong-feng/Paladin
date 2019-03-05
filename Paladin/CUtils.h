#pragma once
#include "CPosition.h"

class CPosition;

class CUtils
{
public:
    // pos λ����� ����������� 
    static void printPerWord(CPosition pos, char *str);

	// pos λ����� str��Ȼ�����
    static void printStringOnPos(CPosition pos, string str);

	//����̨����ƶ�����  pos (y������ *2 )
    static void gotoXY(CPosition pos);

    //����̨����ƶ����� x �У�y ��
    static void gotoXY(int x, int y);

    //����̨���ع����ʾ 
    static void hideCursorDisplay();

    //���ÿ���̨�ı���ɫ
    static void setColor(unsigned short GroundColor = 7);

    //�ƶ�ѡ����(���� �ƶ�  ENTER ȷ��)
    static void moveSelectedUpOrDown(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //sndPlaySound ���ڲ��ű�������
    static void playAsyncMusicRepeatedly(string filePath)
    {
        //�ر�����
        sndPlaySound(NULL, SND_PURGE);

        //խ���ַ�ת��
#ifdef UNICODE
        wstring tmpFilePath = AnsiToUnicode(filePath);
#else
        string tmpFilePath = filePath;
#endif
        //�첽�ظ���������
        sndPlaySound(tmpFilePath.c_str(), SND_ASYNC | SND_LOOP); //�첽����
    }

    //mciSendString ���ڲ�����Ч����ע�⣺�ļ��������пո� ·������ò��������Ҳ��ܹ��� 
    static void playSyncSoundEffect(string filePath)
    {
        //�ر�����
        mciSendString(TEXT("stop effect"), NULL, 0, NULL);
        mciSendString(TEXT("close effect"), NULL, 0, NULL);

        ///��������
        //խ���ַ�ת��
        //�ַ�����ʽ��
        char buffer[1024] = { 0 };
        sprintf_s(buffer, "open %s alias effect", filePath.c_str());

#ifdef UNICODE
        wstring playSoundCmd = AnsiToUnicode(buffer);
#else
        string playSoundCmd = filePath;
#endif
        mciSendString(playSoundCmd.c_str(), NULL, 0, NULL);
        mciSendString(TEXT("play effect"), NULL, 0, NULL);    //ͬ������
    }


private:  //2
    static std::string UnicodeToAnsi(wstring _wStr)
    {
        //---------- �����ַ�ת����խ�ַ� ----------
        int len = WideCharToMultiByte(CP_ACP, 0, _wStr.c_str(), -1, NULL, 0, NULL, NULL);

        char* pStr = new char[len + 1];
        memset(pStr, 0, sizeof(char)*(len + 1));

        WideCharToMultiByte(CP_ACP, 0, _wStr.c_str(), -1, pStr, len, NULL, NULL);
        //-------------------------------------------

        return string(pStr);
    }

    static std::wstring AnsiToUnicode(string _str)
    {
        //---------- ��խ�ַ�ת���ɿ��ַ� ----------
        int len = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, NULL, 0);

        wchar_t* w_pStr = new wchar_t[len + 1];
        memset(w_pStr, 0, sizeof(wchar_t)*(len + 1));

        MultiByteToWideChar(CP_ACP, 0, _str.c_str(), -1, w_pStr, len);
        //-------------------------------------------

        return wstring(w_pStr);
    }



protected:
    //���� ѡ����
    static void moveUp(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //���� ѡ����
    static void moveDown(int& curSelect, int maxNum, CPosition _pos, int backgroundColour, int foregroundColor);

    //����ѡ����
    static void eraserSelect(CPosition _pos, int backgroundColour);

    //��Ⱦѡ����
    static void renderSelect(CPosition _pos, int foregroundColor);

};


