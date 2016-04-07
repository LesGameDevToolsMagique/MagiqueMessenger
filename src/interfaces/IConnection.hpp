//
// Created by Jean-Antoine Dupont on 14/03/2016.
//

#ifndef     __ICONNECTION_HPP__
#define     __ICONNECTION_HPP__

#include    <string>        // std::string
#include    <sys/types.h>   // socket - bind - listen - accept
#include    <sys/socket.h>  // socket - bind - listen - accept
#include    <netinet/in.h>  // sockaddr_in

#define     SOCKET_FD_DEFAULT_VALUE     (-2)

class                                   IConnection
{
protected:
    int                                 socket_fd;
    std::string                         ip_address;
    unsigned int                        port;
    struct sockaddr_in                  my_addr;

/*  Function    */
public:
    virtual ~IConnection() {};

    /*  Getter / Setter         */
    virtual int                         getSocketFd() const = 0;
    virtual const std::string           &getIpAddress() const = 0;
    virtual unsigned int                getPort() const = 0;
    virtual const struct sockaddr_in    *getMySockaddr() const = 0;

    /*  Connection management   */
    virtual int                         connection(const int domain = AF_INET, const int type = SOCK_STREAM,
                                                   const std::string &protocol = std::string()) = 0;
    virtual void                        disconnection() = 0;

    /*  Socket management       */
    virtual int                         createSocket(const int domain, const int type , const int protocol) = 0;
    virtual int                         destroySocket(int fd) = 0;

    virtual int                         bindSocket() = 0;
    virtual int                         listenSocket(const int max_listened = 256) = 0;
    virtual int                         acceptSocket(struct sockaddr *client_addr, socklen_t *client_addr_size) = 0;

protected:
    /*  Configuration           */
    virtual int                         sockaddrConfig(struct sockaddr_in *sockaddr, const int domain = AF_INET) = 0;
};

#endif  /*  __ICONNECTION_HPP__ */
