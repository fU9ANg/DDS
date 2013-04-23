
#ifndef _DDS_NETWORK_DDSOCKETFUNC_H
#define _DDS_NETWORK_DDSOCKETFUNC_H

#include "DDSDefines.h"

namespace DDS
{

namespace NETWORK
{

typedef struct sockaddr SA;

namespace DDSocketFunc
{

const SA* sockaddr_cast (const struct sockaddr_in* sockaddr);
SA*  sockaddr_cast (struct sockaddr_in* sockaddr);
void set_nonblock (int sockfd);
void set_closeonexec (int sockfd);

int  createSocket (void);
void bindToAddr (int sockfd, const struct sockaddr_in& addr);
void listenQueue (int sockfd);
int  acceptConnect (int sockfd, struct sockaddr_in* paddr);
int  connectToServer (int sockfd, const struct sockaddr_in& addr);
void closeSocket (int sockfd);
void shutdownWrite (int sockfd);
void getHostPort (char* buf, size_t size, const struct sockaddr_in& addr);
void setHostPort (const char* ip, uint16_t port, struct sockaddr_in* addr);
int  getSocketError (int sockfd);
struct sockaddr_in getLocalAddr (int sockfd);
struct sockaddr_in getRemoteAddr (int sockfd);
bool isSelf (int sockfd);

inline uint32_t DDS_htonl (uint32_t hostlong)
{
    return (htonl (hostlong));
}

inline uint16_t DDS_htons (uint16_t hostshort)
{
    return (htons (hostshort));
}

inline uint32_t DDS_ntohl (uint32_t netlong)
{
    return (ntohl (netlong));
}

inline uint16_t DDS_ntohs (uint16_t netshort)
{
    return (ntohs (netshort));
}


}
}
}

#endif  //_DDS_NETWORK_DDSOCKETFUNC_H
