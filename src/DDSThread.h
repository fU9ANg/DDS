
#ifndef _DDS_SHAREDLIB_DDSTHREAD_H
#define _DDS_SHAREDLIB_DDSTHREAD_H

#include "DDSDefines.h"

namespace DDS
{
namespace SHAREDLIB
{

class DDSThread
{
    public:
        DDSThread (...);
        ~DDSThread ();

        void Start ();
        void Join  ();

        bool Started () const { return m_started; }
        pid_t gettid () const { return m_tid; }
        const string& name () const { return m_name; }
        static int numCreated () { return m_numCreated; }

    private:
        static void* startThread (void* thread);
        void runInThread (void);
        bool m_started;
        pthread_t m_thread;
        pid_t m_tid;
        string m_name;
};

}
}

#endif // _DDS_SHAREDLIB_DDSTHREAD_H
