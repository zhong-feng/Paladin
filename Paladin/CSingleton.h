//���ã���֤һ����ֻ����һ������
#ifndef _CSingleton_H_
#define _CSingleton_H_

//������ģ��
template<typename T>
class CSingleton
{
public:
    static T* getInstance()
    {
        //��̬�ֲ�����
        static T* m_pSingleton = nullptr;

        if (m_pSingleton == nullptr)
        {
            m_pSingleton = new T();
        }

        return m_pSingleton;
    }


};



#endif