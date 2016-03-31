//
// Created by Jean-Antoine Dupont on 14/03/2016.
//

#ifndef     __IMESSENGER_H__
#define     __IMESSENGER_H__

#include    <sys/socket.h> // sockaddr

class               IMessenger
{
/*  Functions   */
public:
    virtual ~IMessenger() {};

    /*  Message management  */
    virtual int     sendMessage(const int sockfd,
                                const void *message, const unsigned int msg_size,
                                const int flags = 0,
                                const sockaddr *to = nullptr) = 0;

    virtual void    *receiveMessage(const int sockfd,
                                    const unsigned int read_size = 4096,
                                    const int flags = 0,
                                    struct sockaddr *to = nullptr, socklen_t *to_size = nullptr) = 0;
};

#endif  /*  __IMESSENGER_H__    */
