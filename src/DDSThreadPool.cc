
#include "DDSTask.h"
#include "DDSThread.h"
#include "DDSThreadPool.h"

using namespace DDS::SHAREDLIB;

DDSThreadPool::DDSThreadPool (const string& name = string())
    : m_mutex (),
      m_cond (m_mutex),
      m_name (name),
      m_isRuning (false)
{
}

DDSThreadPool::~DDSThreadPool ()
{
}

void DDSThreadPool::Start (int numThreads)
{
    m_numOfThreads = numThreads;
    assert (m_threads.empty ());
    m_isRuning = true;
    m_threads.reserve (numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
        char id[32];
        snprintf (id, sizeof (id), "%d", i);
        m_threads.push_back (new DDSThread (...));
        m_threads[i].Start ();
    }
}

void DDSThreadPool::Stop ()
{
    m_isRuning = false;
    m_cond.Broadcast ();
    for_each (m_threads.begin(), m_threads.end(), ...);
}

void DDSThreadPool::Run (const DDSTask& func)
{
    if (m_threads.empty ())
        getTask ();
    else {
        DDSMutexGuard guard (m_mutex);
        m_tasks.push_back (func);
        m_cond.Signal ();
    }
}

void DDSThreadPool::runInThread ()
{
    try
    {
        while (m_isRuning)
        {
            DDSTask task (getTask ());
            if (task)
                task ();
        }
    }
    catch (const DDSException& ex)
    {
        fprintf (stderr, "exception catch in DDSThreadPool %s\n", \
                 m_name.c_str());
        fprintf (stderr, "reason: %s\n", ex.What ());
        fprintf (stderr, "stack trace: %s\n", ex.stackTrace ());
        abort ();
    }
    catch (const std::exception e)
    {
        fprintf (stderr, "exception catch in DDSThreadPool %s\n", \
                 m_name.c_str());
        fprintf (stderr, "reason: %s\n", e.What ());
        abort ();
    }
    catch (...)
    {
        fprintf (stderr, "unknown exception catch in DDSThreadPool %s\n", \
                 m_name.c_str ());
        abort ();
    }
}

DDSTask DDSThreadPool::getTask ()
{
    DDSMutexGuard guard (m_mutex);
    while (m_tasks.empty() && m_isRuning)
        m_cond.Wait ();

    DDSTask task;
    if (!m_tasks.empty ())
    {
        task = t_tasks.front ();
        t_tasks.pop_front ();
    }
    return (task);
}
