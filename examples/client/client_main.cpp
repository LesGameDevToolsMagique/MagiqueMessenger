//
// Created by Jean-Antoine Dupont on 01/04/2016.
//

#include "../../src/client/Client.hpp"

int main()
{
    IClient *client = new Client("127.0.0.1", 12321);
    std::string msg = "Hello world !";

    if (client->connection(AF_INET, SOCK_STREAM, "TCP") == 0) {
        client->sendMessage(msg, msg.size());

        client->disconnection();
    }

    delete client;

    return 0;
}