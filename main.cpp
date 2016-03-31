#include <iostream>
#include    "src/managers/connection/ConnectionManager.hpp"

int main()
{
    IConnection *connectionManager = new ConnectionManager("127.0.0.1", 12321);

    if (connectionManager->connection(AF_INET, SOCK_STREAM, "TCP") != -1) {
        connectionManager->disconnection();
    }

    delete connectionManager;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}