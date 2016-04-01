//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#ifndef     __CLIENT__HPP__
#define     __CLIENT__HPP__

#include    "../interfaces/IClient.hpp"

class Client : public IClient
{
public:
    Client(const std::string &ip_address, const unsigned int port = 12321);
    virtual ~Client();

    /*  Getter / Setter */
    virtual IConnection *getConnectionManager() const;
    virtual IMessenger  *getMessengerManager() const;

    /*  Connection management   */
    virtual int         connection(const int domain = AF_INET, const int type = SOCK_STREAM,
                                   const std::string &protocol = std::string());
    virtual void        disconnection();

    /*  Message management  */
    virtual int         sendMessage(const void *message, const unsigned int msg_size,
                                    const int flags = 0,
                                    const sockaddr *to = nullptr);

    virtual void        *receiveMessage(const unsigned int read_size = 4096,
                                        const int flags = 0,
                                        struct sockaddr *to = nullptr, socklen_t *to_size = nullptr);
};


#endif  /*  __CLIENT__HPP__ */
