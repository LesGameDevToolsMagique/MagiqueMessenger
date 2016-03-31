#include <iostream>
#include    "src/managers/connection/ConnectionManager.hpp"
#include    "src/managers/messenger/MessengerManager.hpp"

int main()
{
    IConnection *connectionManager = new ConnectionManager("127.0.0.1", 12321);
    IMessenger  *messengerManager = new MessengerManager();
    std::string message = "Coucou toi\n";

    if (connectionManager->connection(AF_INET, SOCK_STREAM, "TCP") != -1) {
        std::cout << "Connected" << std::endl;

        if (messengerManager->sendMessage(connectionManager->getSocketFd(), message.c_str(), message.size()) == 0) {
            std::cout << "Send" << std::endl;
        } else {
            std::cout << "Failed" << std::endl;
        }

        connectionManager->disconnection();
    }

    delete connectionManager;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}