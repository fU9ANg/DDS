
#include "DDSCountDown.h"

using namespace DDS::SHAREDLIB;

DDSCountDown::DDSCountDown (int count)
    : m_mutex(),
      m_cond (m_mutex),
      m_count (count)
{
    // construction code
}

void DDSCountDown::Wait (void)
{
    DDSMutexGuard guard (m_mutex);
    while (m_count > 0)
        m_cond.Wait ();
}

void DDSCountDown::CountDown (void)
{
    DDSMutexGuard guard (m_mutex);
    --m_count;
    if (m_count == 0)
        m_cond.Broadcast ();
}

int DDSCountDown::Count () const
{
    DDSMutexGuard guard (m_mutex);
    return (m_count);
}
