//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#ifndef     __CLIENT__HPP__
#define     __CLIENT__HPP__

#include    "../interfaces/IClient.hpp"

class Client : public IClient
{
public:
    Client(const std::string &ip_address, const unsigned int port = 12321);
    virtual ~Client();

    virtual IConnection *getConnectionManager() const;
    virtual IMessenger *getMessengerManager() const;
};


#endif  /*  __CLIENT__HPP__ */
