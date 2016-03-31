//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#ifndef     __ICLIENT_HPP__
#define     __ICLIENT_HPP__

#include    "IConnection.hpp"
#include    "IMessenger.hpp"

class                   IClient
{
protected:
    IConnection         *connectionManager;
    IMessenger          *messengerManager;

public:
    virtual ~IClient() {};

    virtual IConnection *getConnectionManager() const = 0;
    virtual IMessenger  *getMessengerManager() const = 0;
};

#endif  /*  __ICLIENT_HPP__ */
