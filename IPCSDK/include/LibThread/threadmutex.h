#ifndef JW_CTHREADMUTEX_H_
#define JW_CTHREADMUTEX_H_

#include "LibThread.h"

#ifndef WIN32
#include <pthread.h>
#include <semaphore.h>
#else
#include <windows.h>
#endif

namespace ThreadLib{

#ifndef WIN32
// 线程互斥封装类
class ThreadMutex_Linux
{
    public:
        ThreadMutex_Linux();
        ThreadMutex_Linux(const HsThreadMutex_Linux& other);
        virtual ~ThreadMutex_Linux();

        // 以阻塞方式获取互斥对象
        bool Lock();

        bool TryLock();

        // 释放互斥对象
        void Unlock();

    private:
		ThreadMutex_Linux& operator=(const ThreadMutex_Linux& other);
		void _Initialize();
        // 互斥对象文件描述符
		pthread_mutex_t m_threadMutex;
		pthread_mutexattr_t m_threadAttr;
};
#else //WIN32
class LIBTHREAD_API ThreadMutex_Windows
{
public:
	ThreadMutex_Windows();
	ThreadMutex_Windows(const ThreadMutex_Windows& other);
	virtual ~ThreadMutex_Windows();
	// 以阻塞方式获取互斥对象
	bool Lock();

	bool TryLock();

	// 释放互斥对象
	void Unlock();

private:
	ThreadMutex_Windows& operator=(const ThreadMutex_Windows& other);

	// 互斥对象文件描述符
	CRITICAL_SECTION m_section;
};
#endif //WIN32

#ifndef WIN32
class ThreadMutex : public ThreadMutex_Linux
#else //WIN32
class LIBTHREAD_API ThreadMutex : public ThreadMutex_Windows
#endif //WIN32
{
public:
#ifndef WIN32
	ThreadMutex() :ThreadMutex_Linux(){};
	ThreadMutex(const ThreadMutex& o): ThreadMutex_Linux(o){};
#else
	ThreadMutex() :ThreadMutex_Windows(){};
	ThreadMutex(const ThreadMutex& o): ThreadMutex_Windows(o){};
#endif
	virtual ~ThreadMutex(){};
private:
	ThreadMutex& operator=(const ThreadMutex&)
	{	return *this;	}
};


class LIBTHREAD_API MutexObject
{
    public:
        MutexObject(ThreadMutex& mutex);
        ~MutexObject();

    private:
        ThreadMutex& m_mutex;
        bool m_locked;
};

#ifndef WIN32
class ReadWriteMutex
{
    public:
        ReadWriteMutex();
        ReadWriteMutex(const ReadWriteMutex& other);
        ~ReadWriteMutex();

        ReadWriteMutex& operator =(const ReadWriteMutex& other);
        bool  LockRead();
        bool  LockWrite();

        bool TryLockWrite();
        void Unlock();
    private:
        void _Initialize();
        pthread_rwlock_t m_rwlock;
};
#else //WIN32
class LIBTHREAD_API ReadWriteMutex
{
private:
	int    m_currentLevel;
	int    m_readCount;   
	HANDLE m_unlockEvent; 
	HANDLE m_accessMutex;
	CRITICAL_SECTION m_csStateChange;
	bool lock( int level, int timeout = INFINITE); 
	bool unlock() ;

	ReadWriteMutex& operator =(const ReadWriteMutex& other);
public:
	ReadWriteMutex() ;

	ReadWriteMutex(const ReadWriteMutex& other) ;

	~ReadWriteMutex() ;	

	bool  LockRead();
	bool  LockWrite();

	bool TryLockWrite();
	void Unlock();

};
#endif //WIN32

#ifndef WIN32
class Semphore
{
    public:
        Semphore();
        Semphore(int value);
        ~Semphore();

        bool WaitSem();

        int TimeWaitSem(int msec);

        int TryWaitSem();

        bool PostSem();

        int GetValue();
    private:
        sem_t m_sem;
};
#else //WIN32
class LIBTHREAD_API Semphore
{
public:
	Semphore();
	Semphore(int value);
	~Semphore();

	bool WaitSem();

	int TimeWaitSem(int msec);

    int TryWaitSem();
    
	bool PostSem();

	int GetValue();
private:
	HANDLE m_sem;
};

#endif

#ifndef WIN32
class Event
{
    public:
        Event(bool bSignalFirst = false,bool bManualReset = false);
        ~Event();
        bool WaitEvent();

        int TimeWaitEvent(int msec);

        bool SignalEvent();

        bool ResetEvent( );
        
    private:
        pthread_mutex_t m_thrdmutex;
        pthread_cond_t m_thrdcond;
        bool m_bManualReset ;
        bool m_bSignaled;
};

#else //WIN32
class LIBTHREAD_API Event
{
public:
	Event(bool bInitiallyOwn = FALSE,bool bManualReset = FALSE);

	~Event();

	bool WaitEvent(unsigned int dwTimeOut = INFINITE);

	bool SetEvent( );

	bool ResetEvent( );

private:
	HANDLE m_hEvent;
};

#endif //WIN32

class LIBTHREAD_API ResourceCount
{
public:
	ResourceCount();

	ResourceCount(int count,int size);

	~ResourceCount();

	bool WaitPutResource(int waitTime = -1);

	void PutResource();

	bool WaitTakeResource(int waitTime = -1);

	void TakenResource();

	void IncreaseSize(unsigned int size=1);

	void DecreaseSize(unsigned int size=1);

private:
	int m_size;
	int m_count;
	Semphore m_write_sem;
	Semphore m_read_sem;
};

};

#endif


