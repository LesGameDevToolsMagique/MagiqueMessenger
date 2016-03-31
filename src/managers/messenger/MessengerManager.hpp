//
// Created by Jean-Antoine Dupont on 30/03/2016.
//

#ifndef     __MESSENGERMANAGER_HPP__
#define     __MESSENGERMANAGER_HPP__

#include    "../../interfaces/IMessenger.hpp"

class MessengerManager : public IMessenger
{
public:
    MessengerManager();
    virtual ~MessengerManager();

    /*  Message management  */
    virtual int     sendMessage(const int sockfd,
                                const void *message, const unsigned int msg_size,
                                const int flags = 0,
                                const sockaddr *to = nullptr);

    virtual void    *receiveMessage(const int sockfd,
                                    const unsigned int read_size = 4096,
                                    const int flags = 0,
                                    struct sockaddr *to = nullptr, socklen_t *to_size = nullptr);
};


#endif  /*  __MESSENGERMANAGER_HPP__    */
