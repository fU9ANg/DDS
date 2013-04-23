
#include "DDSException.h"

using namespace DDS::SHAREDLIB;

DDSException::DDSException (const char* what)
    : m_message (what)
{
    FillStackTrace ();
}

DDSException::DDSException (const string& what)
    : m_message (what)
{
    FillStackTrace ();
}

DDSException::~DDSException (void) throw ()
{
}

const char* DDSException::What (void) const throw ()
{
    return (m_message.c_str());
}

const char* DDSException::StackTrace (void) const throw ()
{
    return (m_stack.c_str());
}

void DDSException::FillStackTrace (void)
{
    const int l = 200;
    void* buffer[l];
    int n = ::backtrace (buffer, l);
    char** strings = ::backtrace_symbols (buffer, n);

    if (strings)
    {
        for (int idx=0; idx<n; idx++)
        {
            m_stack.append (strings[idx]);
            m_stack.push_back ('\n');
        }
        free (strings);
    }
}
