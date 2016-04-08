//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#include "../../src/server/Server.hpp"

int main()
{
    IServer *serv = new Server("127.0.0.1", 12321);
    struct client client;

    if (serv->connection(AF_INET, SOCK_STREAM, "TCP") != -1) {

        serv->getConnectionManager()->acceptSocket(&client);

        serv->getMessengerManager()->sendMessage(client.fd, "Coucou\n", 7);

        serv->disconnection();
    }

    delete serv;

    return 0;
}