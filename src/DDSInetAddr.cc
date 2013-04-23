
using namespace DDS::SHAREDLIB;
using namespace DDS::NETWORK;

#include "DDSDefines.h"

DDSInetAddr::DDSInetAddr (uint16_t port)
{
    (void) memset (&m_addr, sizeof (m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = DDSocketFunc::DDS_htonl (...);
    m_addr.sin_port = DDSocketFunc::DDS_htons (port);
}

DDSInetAddr::DDSInetAddr (const string& ip, uint16_t port)
{
    (void) memset (&m_addr, sizeof (m_addr));
    DDSocketFunc::setHostPort (ip.c_str(), port, &m_addr);
}

string DDSInetAddr::getHostPort () const
{
    char buffer[32];
    DDSocketFunc::getHostPort (buffer, sizeof (buffer), m_addr);
    return (buffer);
}
