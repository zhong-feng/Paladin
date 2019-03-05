//作用：保证一个类只产生一个对象
#ifndef _CSingleton_H_
#define _CSingleton_H_

//单例类模板
template<typename T>
class CSingleton
{
public:
    static T* getInstance()
    {
        //静态局部变量
        static T* m_pSingleton = nullptr;

        if (m_pSingleton == nullptr)
        {
            m_pSingleton = new T();
        }

        return m_pSingleton;
    }


};



#endif