
#ifndef _DDS_SHAREDLIB_DDSEXCEPTION_H
#define _DDS_SHAREDLIB_DDSEXCEPTION_H

#include "DDSDefines.h"

using namespace std;

namespace DDS
{
namespace SHAREDLIB
{

class DDSException : public std::exception
{
    public:
        explicit    DDSException (const char*    what);
        explicit    DDSException (const string&  what);
        virtual    ~DDSException (void)       throw ();
        virtual const char* What (void) const throw ();
        const char* StackTrace   (void) const throw ();

    private:
        void FillStackTrace (void);
        string  m_message;
        string  m_stack;
};

}
}
#endif // _DDS_SHAREDLIB_DDSEXCEPTION_H
