//
// Created by Jean-Antoine Dupont on 16/03/2016.
//

#include    "ConnectionManager.hpp"

#include    <iostream>

ConnectionManager::ConnectionManager(const std::string &ip_address, const unsigned int port)
{
    this->socket_fd = SOCKET_FD_DEFAULT_VALUE;
    this->ip_address = ip_address;
    this->port = port;
    std::cout << "[CONNECTION MANAGER]: Object created" << std::endl;
}

ConnectionManager::~ConnectionManager()
{
    this->destroySocket(this->getSocketFd());
    std::cout << "[CONNECTION MANAGER]: Object destroyed" << std::endl;
}

/*
 *    Getter / Setter
 */

/*  Public  */

int                         ConnectionManager::getSocketFd() const
{
    return this->socket_fd;
}

const std::string           &ConnectionManager::getIpAddress() const
{
    return this->ip_address;
}

unsigned int                ConnectionManager::getPort() const
{
    return this->port;
}

const struct sockaddr_in    *ConnectionManager::getMySockaddr() const
{
    return &this->my_addr;
}

/*  Protected   */

int                         ConnectionManager::getProtocol(const std::string &protocol) const
{
    struct protoent         *proto = nullptr;

    if (!protocol.empty()) {
        if ((proto = getprotobyname(protocol.c_str())) == nullptr) {
            std::cout << "[CONNECTION MANAGER]: [ERROR]: Getprotobyname ~> " << strerror(errno) << std::endl;
            return -1;
        }
        return proto->p_proto;
    }

    return 0;
}

/*
 *  Socket management
 */

int                         ConnectionManager::createSocket(const int domain, const int type, const std::string &protocol)
{
    int                     proto = this->getProtocol(protocol);

    if (proto == -1) {
        return -1;
    }

    this->socket_fd = socket(domain, type, proto);

    if (this->socket_fd == -1) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Socket ~> " << strerror(errno) << std::endl;
        this->socket_fd = SOCKET_FD_DEFAULT_VALUE;
        return  -1;
    }

    if (this->sockaddrConfig(&this->my_addr, domain) == -1) {
        return -1;
    }

    std::cout << "[CONNECTION MANAGER]: Socket created" << std::endl;

    return 0;
}

int                         ConnectionManager::destroySocket(int fd)
{
    if (close(fd) == -1) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Close ~> " << strerror(errno) << std::endl;
        return -1;
    }

    this->socket_fd = SOCKET_FD_DEFAULT_VALUE;

    std::cout << "[CONNECTION MANAGER]: Socket destroyed" << std::endl;

    return 0;
}

int                         ConnectionManager::connectSocket()
{
    if (this->getSocketFd() == SOCKET_FD_DEFAULT_VALUE) {
        // TODO: Error message
        return -1;
    }

    if (connect(this->getSocketFd(), (struct sockaddr *)this->getMySockaddr(), sizeof(struct sockaddr)) == -1) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Connect ~> " << strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}

int                         ConnectionManager::bindSocket()
{
    if (this->getSocketFd() == SOCKET_FD_DEFAULT_VALUE) {
        return -1;
    }

    if (bind(this->getSocketFd(), ((struct sockaddr *)this->getMySockaddr()), sizeof(struct sockaddr)) < 0) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Bind ~> " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "[CONNECTION MANAGER]: Socket binded" << std::endl;

    return 0;
}

int                         ConnectionManager::listenSocket(const int max_listened)
{
    if (listen(this->getSocketFd(), max_listened) == -1) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Listen ~> " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "[CONNECTION MANAGER]: Socket listen on " << max_listened << std::endl;

    return 0;
}

int                         ConnectionManager::acceptSocket(struct client *client)
{
    if (client == nullptr) {
        return -1;
    }

    if (client->is_used) {
        return -1;
    }

    int client_fd = accept(this->getSocketFd(), ((struct sockaddr *)&client->addr), &client->size);

    if (client_fd == -1) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Accept ~> " << strerror(errno) << std::endl;
        return -1;
    }

    client->fd = client_fd;
    client->is_used = true;

    std::cout << "[CONNECTION MANAGER]: New client accepted" << std::endl;

    return 0;
}

int                         ConnectionManager::sockaddrConfig(struct sockaddr_in *sockaddr, const int domain)
{
    unsigned int            in_addr = inet_addr(this->getIpAddress().c_str());

    if (in_addr == 0) {
        std::cout << "[CONNECTION MANAGER]: [ERROR]: Inet_addr ~> " << strerror(errno) << std::endl;
        return -1;
    }

    memset(sockaddr, 0, sizeof(sockaddr));

    sockaddr->sin_family = ((sa_family_t)domain);
    sockaddr->sin_addr.s_addr = in_addr;
    sockaddr->sin_port = htons(this->getPort());

    // TODO: sockaddr configuration set

    return 0;
}

