#include <windows.h>
class CritSec
{

public:

	CritSec()
	{
		InitializeCriticalSection(&critSec);
	}

	CritSec(const CritSec& _obj)
	{
		// copy constructor to prevent copying of CRITICAL_SECTION structure
		InitializeCriticalSection(&critSec);
	}

	~CritSec()
	{
		DeleteCriticalSection(&critSec);
	}

	bool TryLock()
	{
		return TryEnterCriticalSection(&critSec) ? true : false;
	}

	void Lock()
	{
		EnterCriticalSection(&critSec);
	}

	void Unlock()
	{
		LeaveCriticalSection(&critSec);
	}

protected:

	CRITICAL_SECTION critSec;

};


class AutoLock
{

public:

	AutoLock(CritSec& critSec)
	{
		m_pCriticalSection = &critSec;
		m_pCriticalSection->Lock();
	}

	~AutoLock()
	{
		m_pCriticalSection->Unlock();
	}

private:

	CritSec* m_pCriticalSection;

};