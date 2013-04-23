
#ifndef _DDS_SHAREDLIB_DDSTHREADPOOL_H
#define _DDS_SHAREDLIB_DDSTHREADPOOL_H

#include "DDSDefines.h"
#include "DDSThread.h"
#include "DDSTask.h"

namespace DDS
{
namespace SHAREDLIB
{

class DDSThreadPool
{
    public:
        explicit DDSThreadPool (const string& name = string());
        ~DDSThreadPool ();

        void Start (int numThreads);
        void Stop  (void);
        void Run   (const DDSTask& func);

    private:
        void runInThread ();
        DDSTask  getTask ();

    private:
        DDSMutexLock        m_mutex;
        DDSCondition        m_cond;
        std::string         m_name;
        vector<DDSThread>   m_threads;
        std::deque<DDSTask> m_tasks;

        bool    m_isRuning;
        int     m_numOfThreads;
};

}
}

#endif // _DDS_SHAREDLIB_DDSTHREADPOOL_H
