
#ifndef _DDS_SHAREDLIB_DDSCONDITION_H
#define _DDS_SHAREDLIB_DDSCONDITION_H

#include "DDSDefines.h"
#include "DDSMutexLockGuard.h"

namespace DDS
{

namespace SHAREDLIB
{

class DDSCondition
{
    public:
        DDSCondition (DDSMutexLock& mutex) : m_mutex (mutex)
        {
            pthread_cond_init (&m_cond, NULL);
        }

        ~DDSCondition (void)
        {
            pthread_cond_destroy (&m_cond);
        }

        void Wait (void)
        {
            pthread_cond_wait (&m_cond, m_mutex.pthreadMutex());
        }

        void Signal (void)
        {
            pthread_cond_signal (&m_cond);
        }

        void Broadcast (void)
        {
            pthread_cond_broadcast (&m_cond);
        }

    private:
        DDSMutexLock& m_mutex;
        pthread_cond_t m_cond;
};

}
}

#endif  // _DDS_SHAREDLIB_DDSCONDITION_H
