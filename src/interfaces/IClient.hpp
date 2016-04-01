//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#ifndef     __ICLIENT_HPP__
#define     __ICLIENT_HPP__

#include    "IConnection.hpp"
#include    "IMessenger.hpp"

class                   IClient
{
protected:
    IConnection         *connectionManager;
    IMessenger          *messengerManager;

/*  Functions   */
public:
    virtual ~IClient() {};

    /*  Getter / Setter */
    virtual IConnection *getConnectionManager() const = 0;
    virtual IMessenger  *getMessengerManager() const = 0;

    /*  Connection management   */
    virtual int         connection(const int domain = AF_INET, const int type = SOCK_STREAM,
                                   const std::string &protocol = std::string()) = 0;
    virtual void        disconnection() = 0;

    /*  Message management  */
    virtual int         sendMessage(const void *message, const unsigned int msg_size,
                                    const int flags = 0,
                                    const sockaddr *to = nullptr) = 0;

    virtual void        *receiveMessage(const unsigned int read_size = 4096,
                                        const int flags = 0,
                                        struct sockaddr *to = nullptr, socklen_t *to_size = nullptr) = 0;
};

#endif  /*  __ICLIENT_HPP__ */
