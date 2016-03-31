//
// Created by Jean-Antoine Dupont on 16/03/2016.
//

#include    "ConnectionManager.hpp"

ConnectionManager::ConnectionManager(const std::string &ip_address, const unsigned int port)
{
    this->socket_fd = SOCKET_FD_DEFAULT_VALUE;
    this->ip_address = ip_address;
    this->port = port;
    this->my_addr = new struct sockaddr_in;
    // TODO: Object created message
}

ConnectionManager::~ConnectionManager()
{
    this->disconnection();
    // TODO: Object destroyed message
}

/*
 *    Getter / Setter
 */

/*  Public  */

int                     ConnectionManager::getSocketFd() const
{
    return this->socket_fd;
}

const std::string       &ConnectionManager::getIpAddress() const
{
    return this->ip_address;
}

unsigned int            ConnectionManager::getPort() const
{
    return this->port;
}

/*  Protected   */

int                     ConnectionManager::getProtocol(const std::string &protocol) const
{
    struct protoent     *proto = nullptr;

    if (!protocol.empty()) {
        if ((proto = getprotobyname(protocol.c_str())) == nullptr) {
            // TODO: Error message
            return -1;
        }
        return proto->p_proto;
    }

    return 0;
}

/*
 *  Connection / Disconnection
 */

int                     ConnectionManager::connection(const int domain, const int type, const std::string &protocol)
{
    int                 proto = this->getProtocol(protocol);

    if (proto == -1) {
        return -1;
    }

    if (this->createSocket(domain, type, proto) == -1) {
        // TODO: Error message
        return -1;
    }

    this->sockaddrConfig(this->my_addr, domain);
    // TODO: Sockaddr config

    if (connect(this->socket_fd, ((struct sockaddr *) nullptr), sizeof(struct sockaddr)) == -1) {
        // TODO: Error message
        return -1;
    }

    // TODO: Connected message

    return 0;
}

void                    ConnectionManager::disconnection()
{
    this->destroySocket();
    // TODO: Disconnected message
}

/*
 *  Socket management
 */

int                     ConnectionManager::createSocket(const int domain, const int type, const int protocol)
{
    this->socket_fd = socket(domain, type, protocol);

    if (this->socket_fd == -1) {
        // TODO: Error message
        this->socket_fd = SOCKET_FD_DEFAULT_VALUE;
        return  -1;
    }

    // TODO: Socket created message
    return 0;
}

void                    ConnectionManager::destroySocket()
{
    if (this->socket_fd != SOCKET_FD_DEFAULT_VALUE) {
        if (close(this->socket_fd) == -1) {
            this->destroySocket();
        }
        this->socket_fd = SOCKET_FD_DEFAULT_VALUE;
        // TODO: Socket destroyed message
    }
}

int                     ConnectionManager::sockaddrConfig(struct sockaddr_in *sockaddr, const int domain)
{
    unsigned int        in_addr = inet_addr(this->getIpAddress().c_str());

    if (in_addr == 0) {
        return -1;
    }

    sockaddr->sin_family = ((sa_family_t) domain);
    sockaddr->sin_port = htons(this->getPort());
    sockaddr->sin_addr.s_addr = in_addr;

    bzero(&(sockaddr->sin_zero), 0);

    // TODO: sockaddr configuration set

    return 0;
}

