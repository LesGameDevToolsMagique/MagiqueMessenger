cmake_minimum_required(VERSION 3.3)
project(MagiqueMessenger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Interfaces
set(INTERFACES_ROOT src/interfaces)
set(INTERFACES_FILES ${INTERFACES_ROOT}/IConnection.h ${INTERFACES_ROOT}/IMessenger.h)

#
# Managers
#
set(MANAGER_ROOT src/managers)

# Connection manager
set(CONNECTION_MANAGER_ROOT ${MANAGER_ROOT}/connection)
set(CONNECTION_MANAGER_FILES ${CONNECTION_MANAGER_ROOT}/ConnectionManager.cpp ${CONNECTION_MANAGER_ROOT}/ConnectionManager.hpp)

# Messenger manager


#
# examples
#
set(EXAMPLE_ROOT examples)

# Client example
set(CLIENT_ROOT ${EXAMPLE_ROOT}/client)

# Server example
set(SERVER_ROOT ${EXAMPLE_ROOT}/server)


# Main
set(SOURCE_FILES  ${INTERFACES_FILES} ${CONNECTION_MANAGER_FILES} main.cpp)
add_executable(MagiqueMessenger ${SOURCE_FILES})