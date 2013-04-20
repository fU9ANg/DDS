

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

namespace DDS
{

namespace sharedLib
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
