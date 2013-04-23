
#ifndef _DDS_NETWORK_DDSOCKETS_H
#define _DDS_NETWORK_DDSOCKETS_H

#include "DDSockets.h"

namespace DDS
{
namespace NETWORK
{

class DDSockets
{
    public:
        explicit DDSockets (int sockFd)
            : m_sockfd (sockFd)
        {}
        ~DDSockets (void);
        int  getFd (void);
        void bindAddress (const DDSInetAddr& localAddr);
        void listen (void);
        int  accpet (DDSInetAddr* peerAddr);
        void shutdownWrite (void);
        void setTcpNoDelay (bool on);
        void setReuseAddr (bool on);

    private:
        const int m_sockfd;
};

}
}

#endif // _DDS_NETWORK_DDSOCKETS_H
