#include <iostream>
#include "src/client/Client.hpp"

int main()
{
    IClient *client = new Client("127.0.0.1", 12321);
    std::string message = "Coucou toi\n";

    if (client->getConnectionManager()->connection(AF_INET, SOCK_STREAM, "TCP") != -1) {

        client->getMessengerManager()->sendMessage(client->getConnectionManager()->getSocketFd(), message.c_str(), message.size());

        client->getConnectionManager()->disconnection();
    }

    delete client;
    return 0;
}