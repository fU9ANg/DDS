
#ifndef _DDS_SHAREDLIB_DDSQUEUE_H
#define _DDS_SHAREDLIB_DDSQUEUE_H

#include "DDSDefines.h"
#include "DDSMutexLockGuard.h"
#include "DDSCondition.h"

namespace DDS
{
namespace SHAREDLIB
{

template <typename type>
class DDSQueue
{
    public:
        DDSQueue (void) : m_mutex(), m_cond(m_mutex), m_queue() {}

        void Push (const type& t)
        {
            DDSMutexGuard guard (m_mutex);
            m_queue.push_back (t);
            m_cond.Signal ();
        }

        type Pop (void)
        {
            DDSMutexGuard guard (m_mutex);
            while (m_queue.empty())
                m_cond.Wait ();
            assert (!m_queue.empty());
            type retType(m_queue.front());
            m_queue.pop_front();
            return (retType);
        }

        size_t Size (void) const
        {
            DDSMutexGuard guard (m_mutex);
            return (m_queue.size());
        }

    private:
        DDSMutexLock        m_mutex;
        DDSCondition        m_cond;
        std::deque<type>    m_queue;
};

}
}
#endif  // _DDS_SHAREDLIB_DDSQUEUE_H
