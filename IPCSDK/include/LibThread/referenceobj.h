#ifndef _LIBTHREAD_INCLUDE_REFERENCEOBJ_H__
#define _LIBTHREAD_INCLUDE_REFERENCEOBJ_H__

#include "LibThread.h"
#include "threadmutex.h"

namespace ThreadLib{

class ThreadMutex;

class LIBTHREAD_API CReferenceObject
{
    public:
        CReferenceObject();
        virtual ~CReferenceObject();

        bool AddReference();

        void ReleaseReference();

        int GetReferenceCount();
    private:
        ThreadMutex m_mutex;
        int m_reference;
};

};

#endif //_LIBTHREAD_INCLUDE_REFERENCEOBJ_H__
