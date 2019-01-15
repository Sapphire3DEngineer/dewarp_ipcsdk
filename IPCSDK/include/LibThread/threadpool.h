#ifndef __SERVER_THREADPOOL_INCLUDE_H__
#define __SERVER_THREADPOOL_INCLUDE_H__

#include "LibThread.h"

namespace ThreadLib{

#ifndef INFINITE 
#define INFINITE ~0
#endif
	class TaskObjectPriv;
	class LIBTHREAD_API TaskObject
	{
	public:
		TaskObject();
		virtual ~TaskObject();

		int WaitTaskFinish(int timeout = INFINITE);

	protected:

		virtual bool OnBeginTask()
		{  return true; }

		virtual unsigned int OnTaskRuning() = 0;

		virtual void OnTaskFinish()
		{	/* nothing to do */	}

	private:
		void PostTaskFinish();
		friend class ThreadItem;
		TaskObjectPriv* m_p;
	};
	
	class ThreadPoolPriv;
	class LIBTHREAD_API ThreadPool
	{
	public:
		ThreadPool();
		virtual ~ThreadPool();

		void SetMaxThreadCount(int count);

		bool RunTask(TaskObject* task);


	private:
		ThreadPoolPriv* m_p;
	};
};

#endif //_JW_THREADBASE_INCLUDE_H_
