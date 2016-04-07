cmake_minimum_required(VERSION 3.3)
project(MagiqueMessenger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Interfaces
set(INTERFACES_ROOT src/interfaces)
set(INTERFACES_FILES ${INTERFACES_ROOT}/IConnection.hpp ${INTERFACES_ROOT}/IMessenger.hpp ${INTERFACES_ROOT}/IClient.hpp)

#
# Managers
#
set(MANAGER_ROOT src/managers)

# Connection manager
set(CONNECTION_MANAGER_ROOT ${MANAGER_ROOT}/connection)
set(CONNECTION_MANAGER_FILES ${CONNECTION_MANAGER_ROOT}/ConnectionManager.cpp ${CONNECTION_MANAGER_ROOT}/ConnectionManager.hpp)

# Messenger manager
set(MESSENGER_MANAGER_ROOT ${MANAGER_ROOT}/messenger)
set(MESSENGER_MANAGER_FILES ${MESSENGER_MANAGER_ROOT}/MessengerManager.cpp ${MESSENGER_MANAGER_ROOT}/MessengerManager.hpp)

#
# Client
#
set(CLIENT_ROOT src/client)
set(CLIENT_FILES ${CLIENT_ROOT}/Client.cpp ${CLIENT_ROOT}/Client.hpp)

#
# Server
#
set(SERVER_ROOT src/server)
set(SERVER_FILES ${SERVER_ROOT}/Server.cpp ${SERVER_ROOT}/Server.hpp)

#
# Examples
#

# Client
set(CLIENT_EXAMPLE_ROOT examples/client)
set(CLIENT_EXAMPLE_FILES ${CLIENT_FILES} ${CLIENT_EXAMPLE_ROOT}/client_main.cpp)
#add_executable(Client ${CONNECTION_MANAGER_FILES} ${MESSENGER_MANAGER_FILES} ${CLIENT_EXAMPLE_FILES})

# Server
set(SERVER_EXAMPLE_ROOT examples/server)

# Main
set(SOURCE_FILES  ${INTERFACES_FILES} ${CONNECTION_MANAGER_FILES} ${MESSENGER_MANAGER_FILES} ${CLIENT_FILES} ${SERVER_FILES} main.cpp)
add_executable(MagiqueMessenger ${SOURCE_FILES})
