#ifndef _DDS_SHAREDLIB_DDSTASK_H
#define _DDS_SHAREDLIB_DDSTASK_H

#include "DDSDefines.h"

class DDSTask
{
    public:
        DDSTask () : m_AutoExit (true)
        {
        }

        virtual ~DDSTask () {};
        virtual int Execute (void* data) = 0;
        bool isAutoExit (void)
        {
            return m_AutoExit;
        }

    private:
        bool m_AutoExit;
        
};

#endif  //_DDS_SHAREDLIB_DDSTASK_H
