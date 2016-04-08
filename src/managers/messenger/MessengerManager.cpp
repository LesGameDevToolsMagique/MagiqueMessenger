//
// Created by Jean-Antoine Dupont on 30/03/2016.
//

#include <new>
#include    "MessengerManager.hpp"

MessengerManager::MessengerManager()
{
}

MessengerManager::~MessengerManager()
{
}

/*
 *  Message manager
 */

int         MessengerManager::sendMessage(const int sockfd,
                                          const void *message, const unsigned int msg_size,
                                          const int flags,
                                          const struct sockaddr *to)
{
    int     send_ret = ((int) sendto(sockfd,
                                    message, msg_size,
                                    flags,
                                    to, ((socklen_t)(to == nullptr ? 0 : sizeof(struct sockaddr)))));

    if (send_ret == -1) {
        // TODO: Error message
        return -1;
    } else if (send_ret != msg_size) {
        // TODO: Error message
        return -2;
    }

    // TODO: Message send

    return 0;
}

void        *MessengerManager::receiveMessage(const int sockfd,
                                              const unsigned int read_size,
                                              const int flags,
                                              struct sockaddr *to, socklen_t *to_size)
{
    void    *msg_rcvd = nullptr;
    int     msg_size = 0;

    msg_rcvd = operator new(read_size);

    msg_size = ((int)recvfrom(sockfd, msg_rcvd, (read_size - 1), flags, to, (to == nullptr ? nullptr : to_size)));

    if (msg_size == -1) {
        // TODO: Error message
        return nullptr;
    }

    ((char *)msg_rcvd)[msg_size] = 0;

    // TODO: Message received

    return msg_rcvd;
}


