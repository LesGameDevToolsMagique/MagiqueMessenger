//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#ifndef     __ISERVER_HPP__
#define     __ISERVER_HPP__

#include    "IConnection.hpp"
#include    "IMessenger.hpp"
#include    <list>

class                                   IServer
{
protected:
    IConnection                         *connectionManager;
    IMessenger                          *messageManager;
    std::list<struct client *>          clients;

public:
    virtual ~IServer() {};

    /*  Getter / Setter */
    virtual IConnection                 *getConnectionManager() const = 0;
    virtual IMessenger                  *getMessengerManager() const = 0;
    virtual const std::list<client *>   &getClientsList() const = 0;

    /*  Connection management   */
    virtual int                         connection(const int domain = AF_INET, const int type = SOCK_STREAM,
                                                   const std::string &protocol = std::string(),
                                                   const unsigned int max_listener = 128) = 0;
    virtual void                        disconnection() = 0;

    /*  Message management  */
    virtual int                         sendMessage(const struct client *client,
                                                    const void *message, const unsigned int msg_size,
                                                    const int flags) = 0;

    virtual void                        *receiveMessage(const unsigned int read_size = 4096,
                                                        const int flags = 0,
                                                        struct sockaddr *to = nullptr, socklen_t *to_size = nullptr) = 0;
};

#endif  /*  __ISERVER_HPP__ */
