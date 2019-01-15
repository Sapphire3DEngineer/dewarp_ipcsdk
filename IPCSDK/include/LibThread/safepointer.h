#ifndef __SERVER_SAFEPOINTER_INCLUDE_H__
#define __SERVER_SAFEPOINTER_INCLUDE_H__

#include "LibThread.h"
#include "threadmutex.h"

namespace ThreadLib{

	class CPointerKeeperPriv;
	class LIBTHREAD_API CPointerKeeper
	{
	public:
		CPointerKeeper();

		~CPointerKeeper();

		static CPointerKeeper& Instance();

		void* AddReference(void* p);

		void* DelReference(void* p);

	private:
		CPointerKeeperPriv* m_p;
	};


	template<class T>
	class CSafePointer
	{
		ThreadMutex m_mutex;
		T m_ptr;
	public:

		CSafePointer()
		{
			m_ptr = NULL;
		}

		CSafePointer(T v)
		{
			m_ptr = NULL;
			Set(v);
		}

		CSafePointer(const CSafePointer<T>& other)
		{
			m_ptr = NULL;
			const_cast<CSafePointer<T>&>(other).Lock();
			Set(other.Get());
			const_cast<CSafePointer<T>&>(other).Unlock();
		}

		~CSafePointer()
		{
			Release();
		}

		bool Lock()
		{
			return m_mutex.Lock();
		}

		void Unlock()
		{
			m_mutex.Unlock();
		}

		void Set(T v)
		{
			Release();
			m_mutex.Lock();
			m_ptr =(T) CPointerKeeper::Instance().AddReference(v);
			m_mutex.Unlock();
		}

		T Get()
		{	
			return m_ptr;
		}

		T Get() const
		{	
			return m_ptr;	
		}

		bool Valid()
		{  
			return (m_ptr); 
		}

		void Release()
		{
			m_mutex.Lock();
			T p = (T)CPointerKeeper::Instance().DelReference(m_ptr);
			m_ptr = NULL;
			m_mutex.Unlock();
			if (p){
				delete (T)p;
			}
			
		}

		CSafePointer<T>& operator =(T v)
		{
			if (m_ptr != v){
				Set(v);
			}
			return *this;
		}

		CSafePointer<T>& operator =(const CSafePointer<T>& other)
		{
			if (this!=&other){
				const_cast<CSafePointer<T>&>(other).Lock();
				Set(other.Get());
				const_cast<CSafePointer<T>&>(other).Unlock();
			}			
			return *this;
		}

		operator T()
		{	
			return m_ptr; 
		}

		operator T() const
		{	
			return m_ptr;	
		}

		T operator->()
		{	
			return m_ptr;	
		}

		T operator->() const
		{	
			return m_ptr;	
		}
	};
};

#endif // __SERVER_SAFEPOINTER_INCLUDE_H__
