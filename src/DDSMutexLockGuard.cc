
#include "DDSMutexLockGuard.h"

using namespace DDS::SHAREDLIB;

DDSMutexLock::DDSMutexLock (void)
{
    pthread_mutex_init (&m_mutex, NULL);
}

DDSMutexLock::~DDSMutexLock (void)
{
    pthread_mutex_destroy (&m_mutex);
}

void DDSMutexLock::Lock (void)
{
    pthread_mutex_lock (&m_mutex);
}

void DDSMutexLock::unLock (void)
{
    pthread_mutex_unlock (&m_mutex);
}

pthread_mutex_t* DDSMutexLock::pthreadMutex (void)
{
    return &m_mutex;    // quake
}

DDSMutexGuard::~DDSMutexGuard (void)
{
    m_lock.unLock ();
}
