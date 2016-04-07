//
// Created by Jean-Antoine Dupont on 07/04/2016.
//

#include    "Server.hpp"
#include    "../managers/connection/ConnectionManager.hpp"
#include    "../managers/messenger/MessengerManager.hpp"

Server::Server(const std::string &ip_address, const unsigned int port)
{
    this->connectionManager = new ConnectionManager(ip_address, port);
    this->messageManager = new MessengerManager();
}

Server::~Server()
{
    delete this->connectionManager;
    delete this->messageManager;

    this->clearClientsList();
    this->clients.clear();
}

/*
 *  Getter / Setter
 */

IConnection                                 *Server::getConnectionManager() const
{
    return this->connectionManager;
}

IMessenger                                  *Server::getMessengerManager() const
{
    return this->messageManager;
}

const std::list<client *>                   &Server::getClientsList() const
{
    return this->clients;
}

/*
 *  Connection management
 */

int                                         Server::connection(const int domain, const int type, const std::string &protocol,
                                                               const unsigned int max_listener)
{
    if (this->getConnectionManager()->connection(domain, type, protocol) == -1) {
        return -1;
    }

    if (this->getConnectionManager()->bindSocket() == -1) {
        return -1;
    }

    if (this->getConnectionManager()->listenSocket(max_listener) == -1) {
        return -1;
    }

    for (int i = 0 ; i <= max_listener ; i++) {
        struct client *new_client = new(struct client);
        new_client->is_used = false;

        this->clients.push_back(new_client);
    }

    return 0;
}

void                                            Server::disconnection()
{
    this->getConnectionManager()->disconnection();
}

/*
 *  Messenger management
 */

int                                             Server::sendMessage(const void *message, const unsigned int msg_size,
                                    const int flags, const sockaddr *to)
{
    return this->getMessengerManager()->sendMessage(this->getConnectionManager()->getSocketFd(), message, msg_size, flags, to);
}

void                                            *Server::receiveMessage(const unsigned int read_size,
                                                                        const int flags, sockaddr *to, socklen_t *to_size)
{
    return this->getMessengerManager()->receiveMessage(this->getConnectionManager()->getSocketFd(), read_size, flags, to,to_size);
}

/*
 *  Other
 */

void                                            Server::clearClientsList()
{
    std::list<struct client *>::const_iterator  it;
    struct client                               *client = nullptr;

    for (it = this->getClientsList().begin() ; it != this->getClientsList().end() ; it++) {
        client = *it;

        this->getConnectionManager()->destroySocket(client->fd);

        delete client;

        this->clients.erase(it);

        client = nullptr;
    }
}