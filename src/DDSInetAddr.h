
#ifndef _DDS_NETWORK_DDSINETADDR_H
#define _DDS_NETWORK_DDSINETADDR_H

using namespace DDS::NETWORK;
using namespace DDS::SHAREDLIB;
namespace DDS
{
namespace NETWORK
{

class DDSInetAddr
{
    public:
        explicit DDSInetAddr (uint16_t port);
        DDSInetAddr (const string& ip, uint16_t port);

        DDSInetAddr (const struct sockaddr_in& addr)
            : m_addr (addr)
        {}

        string getHostPort () const;

        const struct sockaddr_in& getInetAddr () const
        { return m_addr; }

        void setInetAddr (const struct sockaddr_in& addr)
        { m_addr = addr; }

    private:
        struct sockaddr_in m_addr;
};

}
}

#endif // _DDS_NETWORK_DDSINETADDR_H
