//
// Created by Jean-Antoine Dupont on 16/03/2016.
//

#ifndef     __CONNECTIONMANAGER_HPP__
#define     __CONNECTIONMANAGER_HPP__

#include    "../../interfaces/IConnection.h"

#include    <netdb.h>       // getprotobyname - struct protoent
#include    <arpa/inet.h>   // inet_addr

class                                   ConnectionManager: public IConnection
{
/*  Functions   */
public:
    ConnectionManager(const std::string &ip_address, const unsigned int port = 4242);
    virtual ~ConnectionManager();

    /*  Getter / Setter         */
    virtual int                         getSocketFd() const;
    virtual const std::string           &getIpAddress() const;
    virtual unsigned int                getPort() const;
    virtual const struct sockaddr_in    *getMySockaddr() const;

    /*  Connection management   */
    virtual int                         connection(const int domain = AF_INET, const int type = SOCK_STREAM, const std::string &protocol = std::string());
    virtual void                        disconnection();

protected:
    /*  Getter / Setter         */
    int                                 getProtocol(const std::string &protocol) const;

    /*  Socket management       */
    virtual int                         createSocket(const int domain, const int type , const int protocol);
    virtual void                        destroySocket();

    /*  Configuration           */
    virtual int                         sockaddrConfig(struct sockaddr_in *sockaddr, const int domain = AF_INET);
};


#endif  /*  __CONNECTIONMANAGER_HPP__   */
