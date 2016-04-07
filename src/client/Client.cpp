//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#include    "Client.hpp"
#include    "../managers/connection/ConnectionManager.hpp"
#include    "../managers/messenger/MessengerManager.hpp"

Client::Client(const std::string &ip_address, const unsigned int port)
{
    this->connectionManager = new ConnectionManager(ip_address, port);
    this->messengerManager = new MessengerManager();
}

Client::~Client()
{
    delete this->connectionManager;
    delete this->messengerManager;
}

/*
 *  Getter / Setter
 */

IConnection     *Client::getConnectionManager() const
{
    return this->connectionManager;
}

IMessenger      *Client::getMessengerManager() const
{
    return this->messengerManager;
}

/*
 *  Connection management
 */

int             Client::connection(const int domain, const int type, const std::string &protocol)
{
    return this->getConnectionManager()->connection(domain, type, protocol);
}

void            Client::disconnection()
{
    this->getConnectionManager()->disconnection();
}

/*
 *  Messenger management
 */

int             Client::sendMessage(const void *message, const unsigned int msg_size, const int flags, const sockaddr *to)
{
    return this->getMessengerManager()->sendMessage(this->getConnectionManager()->getSocketFd(), message, msg_size, flags, to);
}

void            *Client::receiveMessage(const unsigned int read_size, const int flags, sockaddr *to, socklen_t *to_size)
{
    return this->getMessengerManager()->receiveMessage(this->getConnectionManager()->getSocketFd(), read_size, flags, to,to_size);
}