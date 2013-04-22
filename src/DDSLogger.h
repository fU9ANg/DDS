
#ifndef _DDS_SHAREDLIB_DDSLOGGER_H
#define _DDS_SHAREDLIB_DDSLOGGER_H

#include "DDSDefines.h"

namespace DDS
{
namespace SHAREDLIB
{

class DDSLogger
{

    public:
        enum eLevel
        {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            NUMBER_OF_LOGTYPE,
        };

        DDSLogger (const char* file, int line);
        DDSLogger (const char* file, int line, eLevel lvl);
        DDSLogger (const char* file, int line, eLevel lvl, const char* func);
        DDSLogger (const char* file, int line, bool abort);

        ~DDSLogger (void);

        std::ostream& stream();

        static eLevel Level (void);
        static void setLevel (eLevel lvl);

};

#define LOG_TRACE if (DDSLogger::Level() <= DDSLogger::TRACE) \
                      DDSLogger(__FILE__, __LINE__, DDSLogger::TRACE, __func__).stream()
#define LOG_DEBUG     DDSLogger(__FILE__, __LINE__, DDSLogger::DEBUG, __func__).stream()
#define LOG_INFO      DDSLogger(__FILE__, __LINE__).stream()
#define LOG_WARN      DDSLogger(__FILE__, __LINE__, DDSLogger::WARN).stream()
#define LOG_ERROR     DDSLogger(__FILE__, __LINE__, DDSLogger::ERROR).stream()
#define LOG_FATAL     DDSLogger(__FILE__, __LINE__, DDSLogger::FATAL).stream()
#define LOG_SYSERR    DDSLogger(__FILE__, __LINE__, false).stream();
#define LOG_SYSFATAL  DDSLogger(__FILE__, __LINE__, true).stream();

#define CHECK_NOTNULL(val) \
    ::DDS::sharedLib::CheckNotNULL(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

template <typename T>
T* CheckNotNULL (const char* file, int line, const char* names, T* ptr)
{
    if (ptr == NULL) {
        DDSLogger (file, line, DDSLogger::FATAL).stream() << names;
    }

    return ptr;
}

}
}

#endif  // _DDS_SHAREDLIB_DDSLOGGER_H
