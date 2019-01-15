#ifndef __SERVER_THREADBASE_INCLUDE_H__
#define __SERVER_THREADBASE_INCLUDE_H__

#include "threadmutex.h"
#include "LibThread.h"

namespace ThreadLib{

#ifndef INFINITE 
#define INFINITE ~0
#endif

#define THREAD_STACK_SIZE 1*1024*1024

class LIBTHREAD_API CRepetition
{
public:
	CRepetition();
	virtual ~CRepetition();

	void SetExit(bool exit = true);
	bool IsExit();

	virtual int Init() ;

	virtual unsigned int Run() ;

	virtual unsigned int Repetition() = 0;

	virtual unsigned int ExitRun();

	virtual unsigned int Exit();

	virtual unsigned int RunProc();
private:
	volatile bool m_exit;
};


#ifdef WIN32
// CThread_Windows  class is the base class which wrap thread windows api
// Derived class should re-implement at lease one of those virtual function
class LIBTHREAD_API CThread_Windows : protected CRepetition
{
public:
	CThread_Windows(bool auto_del = false);
	virtual ~CThread_Windows ();

	// start thread if not exist create one
    bool CreateThread(bool start = true,int stacksize = 0);

	// exited the thread
	unsigned int DestroyThread();

	bool WaitExit(unsigned int timeout = INFINITE);

	bool IsCreated();

	bool Resume();

	// suspend thread
	unsigned int Suspend();

protected:

	virtual void OnAutoDeleteObj();

	bool WaitForExit(HANDLE threadHandle,unsigned int timeout = INFINITE);
private:
	static unsigned int __stdcall ThreadProc(void* lpParameter);
	ThreadMutex m_handleMutex;
	HANDLE m_threadHandle;
	unsigned int m_threadId;
	bool m_auto_del;
};

#else

#include <pthread.h>

#ifndef INVALID_THREAD_PID
#define INVALID_THREAD_PID 0
#endif
// 线程类，封装了线程的创建与使用 API
class CThread_Linux : protected CRepetition 
{
    public:
        CThread_Linux();
        virtual ~CThread_Linux();

        // 创建线程
        bool CreateThread(bool start = true,int stacksize = THREAD_STACK_SIZE);

        // exited the thread
        unsigned int DestroyThread();

        bool IsCreated();

        bool WaitExit(unsigned int timeout = INFINITE);

        // 唤醒线程
        void Wakeup();
    protected:		

        // 等待线程被唤醒
        void WaitWakeup();

        // 等待线程结束
        void WaitForExit(pthread_t pid);
    private:
        Event m_IdleCond;
        ThreadMutex m_pidMutex;
        pthread_t m_pid;
        pthread_attr_t m_attr;
        static void* ThreadProc(void* arg);

        volatile bool m_exit;
        bool m_start_instant;
};
#endif

#ifdef WIN32
class LIBTHREAD_API Thread : public CThread_Windows  
{
#else
class Thread  : public CThread_Linux 
{
#endif
public:
	Thread(){}
	virtual ~Thread(){}
};

};

#endif //_JW_THREADBASE_INCLUDE_H_
