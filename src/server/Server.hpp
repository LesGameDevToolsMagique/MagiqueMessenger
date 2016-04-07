//
// Created by Jean-Antoine Dupont on 07/04/2016.
//

#ifndef     __SERVER_HPP__
#define     __SERVER_HPP__

#include    "../interfaces/IServer.hpp"

class                                   Server : public IServer
{
public:
    Server(const std::string &ip_address, const unsigned int port = 12321);
    virtual ~Server();

    /*  Getter / Setter */
    virtual IConnection                 *getConnectionManager() const;
    virtual IMessenger                  *getMessengerManager() const;
    virtual const std::list<client *>   &getClientsList() const

    /*  Connection management   */
    virtual int                         connection(const int domain = AF_INET, const int type = SOCK_STREAM,
                                                   const std::string &protocol = std::string(),
                                                   const unsigned int max_listener = 128);
    virtual void                        disconnection();

    /*  Message management  */
    virtual int                         sendMessage(const void *message, const unsigned int msg_size,
                                                    const int flags = 0,
                                                    const sockaddr *to = nullptr);

    virtual void                        *receiveMessage(const unsigned int read_size = 4096,
                                                        const int flags = 0,
                                                        struct sockaddr *to = nullptr, socklen_t *to_size = nullptr);

protected:
    void                                clearClientsList();
};


#endif  /*  __SERVER_HPP__  */
