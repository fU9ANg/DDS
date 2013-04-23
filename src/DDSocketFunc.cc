
#include "DDSocketFunc.h"

#include "DDSQueue.h"
#include "DDSMutexLockGuard.h"
#include "DDSingle.h"

using namespace DDS::NETWORK;

namespace
{

const SA* sockaddr_cast (const struct sockaddr_in* sockaddr)
{
    return ((const SA*) ((const void*) sockaddr));
}

SA* sockaddr_cast (struct sockaddr_in* sockaddr)
{
    return ((SA*) ((void*) sockaddr));
}

void set_nonblock (int sockfd)
{
    int flags;
    if ((flags = ::fcntl (sockfd, F_GETFL, 0)) < 0) {
        std::cout << "SYSERROR: " << std::endl;
    }
    flags |= O_NONBLOCK;
    if (::fcntl (sockfd, F_GETFL, flags) < 0) {
        std::cout << "SYSERROR: " << std::endl;
    }
}

// 如果对描述符设置了FD_CLOEXEC，使用execl执行的程序里，此描述符被关闭，不能再使用它
void set_closeonexec (int sockfd)
{
    int flags = ::fcntl (sockfd, F_GETFD, 0);
    flags |= O_CLOEXEC;
    if (::fcntl (sockfd, F_GETFD, flags) < 0) {
        std::cout << "SYSERROR: " << std::endl;
    }
}
}

int DDSocketFunc::createSocket (void)
{
    int sockfd;
    if ((sockfd = ::socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        std::cout << "SYSERROR: " << std::endl;
    }

    set_nonblock (sockfd);
    set_closeonexec (sockfd);

    return (sockfd);
}

void DDSocketFunc::bindToAddr (int sockfd, const struct sockaddr_in& addr)
{
    int ret;
    if ((ret = ::bind (sockfd, sockaddr_cast (&addr), sizeof (addr))) < 0) {
        std::cout << "SYSERROR: ::bind" << std::endl;
    }
}

void DDSocketFunc::listenQueue (int sockfd)
{
    int ret;
    if ((ret = ::listen (sockfd, SOMAXCONN)) < 0) {
        std::cout << "SYSERROR: ::listenQueue" << std::endl;
    }
}

int DDSocketFunc::acceptConnect (int sockfd, struct sockaddr_in* paddr)
{
    socklen_t addr_len = sizeof (*paddr);
    int connfd;

    if ((connfd = ::accept (sockfd, sockaddr_cast (paddr), &addr_len)) < 0) {

        int Errno = errno;
        std::cout << "SYSERR: ::accept" << std::endl;

        switch (Errno) {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO:
            case EPERM:
            // expected errors
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case EMFILE:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                break;
            default:
                break;
        }
    }

    set_nonblock (connfd);
    set_closeonexec (connfd);

    return (connfd);
}

int DDSocketFunc::connectToServer (int sockfd, const struct sockaddr_in& addr)
{
    int res;

    if ((res = ::connect (sockfd, sockaddr_cast (&addr), sizeof (addr))) < 0) {
        std::cout << "SYSERROR: ::connect" << std::endl;
    }

    return (res);
}

void DDSocketFunc::closeSocket (int sockfd)
{
    if (sockfd)
        ::close (sockfd);
}

void DDSocketFunc::shutdownWrite (int sockfd)
{
    if (::shutdown (sockfd, SHUT_WR) < 0) {
        std::cout << "SYSERROR: ::shutdownWrite" << std::endl;
    }
}

void DDSocketFunc::getHostPort (char* buf, size_t size, \
                               const struct sockaddr_in& addr)
{
    char host[INET_ADDRSTRLEN] = "INVALID";
    ::inet_ntop (AF_INET, &addr.sin_addr, host, sizeof (host));
    uint16_t port = DDS_ntohs (addr.sin_port);
    snprintf (buf, size, "%s:%u", host, port);
}

void DDSocketFunc::setHostPort (const char* ip, uint16_t port, \
                               struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons (port);
    if (inet_pton (AF_INET, ip, &addr->sin_addr) <= 0) {
        std::cout << "SYSERROR: ::setHostPort" << std::endl;
    }
}

int DDSocketFunc::getSocketError (int sockfd)
{
    int optval;

    socklen_t optlen = sizeof (optval);
    if (::getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        return (errno);
    }
    else {
        return (optval);
    }
}

struct sockaddr_in DDSocketFunc::getLocalAddr (int sockfd)
{
    struct sockaddr_in localaddr;
    (void) memset (&localaddr, 0x00, sizeof (localaddr));
    socklen_t addr_len = sizeof (localaddr);

    if (::getsockname (sockfd, sockaddr_cast (&localaddr), &addr_len) < 0) {
        std::cout << "SYSERROR: ::getsockname" << std::endl;
    }

    return (localaddr);
}

struct sockaddr_in DDSocketFunc::getRemoteAddr (int sockfd)
{
    struct sockaddr_in remoteaddr;
    (void) memset (&remoteaddr, 0x00, sizeof (remoteaddr));
    socklen_t addr_len = sizeof (remoteaddr);

    if (::getpeername (sockfd, sockaddr_cast (&remoteaddr), &addr_len) < 0) {
        std::cout << "SYSERROR: ::getpeername" << std::endl;
    }

    return (remoteaddr);
}

bool DDSocketFunc::isSelf (int sockfd)
{
    struct  sockaddr_in localaddr = getLocalAddr (sockfd);
    struct  sockaddr_in remoteaddr = getRemoteAddr (sockfd);

    return ((localaddr.sin_port == remoteaddr.sin_port) &&
            (localaddr.sin_addr.s_addr == remoteaddr.sin_addr.s_addr));
}
