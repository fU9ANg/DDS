
#include "DDSLogger.h"

using namespace DDS::SHAREDLIB;

class DDSLOGGER
{
    public:
        DDSLOGGER (DDSLogger::eLevel lvl, int old_errno, const char* file, int line);
        void Done ();

        std::ostringstream m_stream;
        DDSLogger::eLevel  m_level;

        const char*        m_fullname;
        const char*        m_function;
        const char*        m_basename;
        int                m_line;

        static const char* m_LogLevelName[];
};

__thread char errnobuf[512];

const char* StrError (int saved_errno)
{
    return (strerror_r (saved_errno, errnobuf, sizeof (errnobuf)));
}

DDSLogger::eLevel initLogLevel ()
{
    if (::getenv ("DDS_LOG_TRACE"))
        return DDSLogger::TRACE;
    else
        return DDSLogger::DEBUG;
}

DDSLogger::eLevel g_level = initLogLevel ();

const char* DDSLOGGER::m_LogLevelName[DDSLogger::NUMBER_OF_LOGTYPE] = 
{
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL",
};

DDSLOGGER::DDSLOGGER (DDSLogger::eLevel lvl, int saved_errno, const char* file, int line)
    : m_level (lvl),
      m_stream (),
      m_fullname (file),
      m_line (line),
      m_basename (NULL),
      m_function (NULL)
{
    const char* path_pos = strrchr (m_fullname, '/');
    char msg_head[512];
    m_basename = (path_pos != NULL) ? path_pos + 1 : m_fullname;
    snprintf (msg_head, sizeof (msg_head), "%s %5d %s ",
            m_time.toFormattedString().c_str(), CurrentThread::tid(),
            m_LogLevelName[lvl]);

    m_stream << msg_head;

    if (saved_errno != 0)
        m_stream << StrError (saved_errno) << " (errno=" << saved_errno << ") ";
}

void DDSLOGGER::Done ()
{
    m_stream << " - " << m_basename << ":" << m_line << '\n';
}


std::ostream& DDSLogger::stream ()
{
    return (m_log->m_stream);
}

DDSLogger::DDSLogger (const char* file, int line)
    : m_log (new DDSLOGGER (INFO, 0, file, line))
{
}

DDSLogger::DDSLogger (const char* file, int line, DDSLogger::eLevel lvl, char* func)
    : m_log (new DDSLOGGER (lvl,  0, file, line))
{
    m_log->m_stream << func << ' ';
}

DDSLogger::DDSLogger (const char* file, int line, DDSLogger::eLevel lvl)
    : m_log (new DDSLOGGER (lvl,  0, file, line))
{
}

DDSLogger::DDSLogger (const char* file, int line, bool bAbort)
    : m_log (new DDSLOGGER (bAbort?FATAL:ERROR, errno, file, line))
{
}

DDSLogger::~Logger ()
{
    m_log->Done ();

    std::string buf (m_log->m_stream.str());
    ssize_t n = ::write (1, buf.data(), buf.size());
    (void)n;
    if (m_log->m_level == FATAL)
        abort ();
}

DDSLogger::eLevel DDSLogger::Level ()
{
    return (g_level);
}

void DDSLogger::setLevel (DDSLogger::eLevel lvl)
{
    g_level = lvl;
}
