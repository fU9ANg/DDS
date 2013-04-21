
#ifndef _DDS_SHAREDLIB_DDSCOUNTDOWN_H
#define _DDS_SHAREDLIB_DDSCOUNTDOWN_H

#include "DDSDefines.h"
#include "DDSMutexLockGuard.h"
#include "DDSCondition.h"

namespace DDS
{
namespace SHAREDLIB
{

class DDSCountDown
{
    public:
        DDSCountDown (int count);
        void Wait (void);
        void CountDown (void);
        int Count () const;

    private:
        mutable DDSMutexLock m_mutex;
        DDSCondition         m_cond;
        int                  m_count;
};

}
}
#endif  // _DDS_SHAREDLIB_DDSCOUNTDOWN_H
