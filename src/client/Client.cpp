//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#include "Client.hpp"
#include "../managers/connection/ConnectionManager.hpp"
#include "../managers/messenger/MessengerManager.hpp"

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