#ifndef _LIBTHREAD_INCLUDE_IDMANAGER_H__
#define _LIBTHREAD_INCLUDE_IDMANAGER_H__

#include "LibThread.h"
#include "referenceobj.h"
#include <map>

namespace ThreadLib{

class LIBTHREAD_API CReferenceIdObject : public CReferenceObject
{
    public:
        CReferenceIdObject();
        virtual ~CReferenceIdObject();
        int GetID();
    protected:
        friend class CReferenceObjectMgr;
        void SetID(int id);
    private:
        int m_id;
};

class ReadWriteMutex;
class LIBTHREAD_API CReferenceObjectMgr
{
    public:
        CReferenceObjectMgr();
        virtual ~CReferenceObjectMgr();

        CReferenceIdObject * GetReferenceObj(int id);

        bool ReleaseRefObj(CReferenceIdObject * obj);

        bool AddObject(CReferenceIdObject * obj);

		bool AddObjectToMap(int id,CReferenceIdObject * obj);

        bool RemoveObject(int id);

        void RemoveAllObject();

        bool BeginGet();
        CReferenceIdObject* GetNext();
        void EndGet();
    private:
        ReadWriteMutex* m_lock;
        typedef std::map<int,CReferenceIdObject *> OBJ_MAP_T;
        typedef OBJ_MAP_T::iterator  OBJ_MAP_ITOR_T;
        OBJ_MAP_ITOR_T m_current_iter;
        OBJ_MAP_T m_obj_map;
        int m_curr_index;
};

};

#endif

