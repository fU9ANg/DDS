
#include "DDSockets.h"

DDSockets::~DDSockets (void)
{
    DDSocketFunc::close (m_sockfd);
}

int DDSockets::getFd (void)
{
    return (m_sockfd);
}

void DDSockets::bindAddress (const DDSInetAddr& localAddr)
{
    DDSocketFunc::bindToAddr (m_sockfd, localAddr.getInetAddr ());
}

void DDSockets::listen (void)
{
    DDSocketFunc::listenQueue (m_sockfd);
}

int DDSockets::accpet (DDSInetAddr* peerAddr)
{
    struct sockaddr_in addr;
    int connfd = DDSocketFunc::acceptConnect (m_sockfd, &addr);
    (void) memset (&addr, 0x00, sizeof (addr));

    if (connfd >= 0)
        peeraddr->setInetAddr (addr);

    return (connfd);
}

void DDSockets::shutdownWrite (void)
{
    DDSocketFunc::shutdownWrite (m_sockfd);
}

void DDSockets::setTcpNoDelay (bool on)
{
    int opt_val = on ? 1 : 0;
    ::setsockopt (m_sockfd, IPPROTO_TCP, TCP_NODELAY, \
                  &opt_val, sizeof (opt_val));
}

void DDSockets::setReuseAddr (bool on)
{
    int opt_val = on ? 1 : 0;
    ::setsockopt (m_sockfd, SOL_SOCKET, SO_REUSEADDR, \
                  &opt_val, sizeof (opt_val));
}
