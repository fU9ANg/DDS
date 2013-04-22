
#ifndef _DDS_SHAREDLIB_DDSMUTEXLOCKGUARD_H
#define _DDS_SHAREDLIB_DDSMUTEXLOCKGUARD_H

#include "DDSDefines.h"

namespace DDS
{

namespace SHAREDLIB
{

class DDSMutexLock
{
    public:
        DDSMutexLock (void);
        ~DDSMutexLock (void);

        void Lock (void);
        void unLock (void);
        pthread_mutex_t* pthreadMutex (void);
    private:
        DDSMutexLock (const DDSMutexLock&);
        const DDSMutexLock& operator= (const DDSMutexLock&);
        pthread_mutex_t m_mutex;
};

class DDSMutexGuard
{
    public:
        explicit DDSMutexGuard (DDSMutexLock& lock) : m_lock (lock)
        {
            m_lock.Lock ();
        }

        ~DDSMutexGuard (void);
    private:
        DDSMutexGuard (const DDSMutexGuard&);
        const DDSMutexGuard& operator= (const DDSMutexGuard&);
        DDSMutexLock& m_lock;
};


}
}

#endif  // _DDS_SHAREDLIB_DDSMUTEXLOCKGUARD_H
