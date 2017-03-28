/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "Client.hpp"
#include "ClientException.hpp"

/**
 * New instance with given host name and port.
 *
 * @param host
 * @param port
 */
Client::Client(const string host, const string port) {
    serverHost = host;
    serverPort = port;
}

/**
 * Establish connection to the server.
 *
 * @since 2017.03.29
 */
void Client::connectToServer() {
    int status;
    struct addrinfo *info;

    for (info = serverInfo; NULL != info; info = info->ai_next) {
        serverSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

        if (-1 == serverSocket) {
            continue;
        }

        status = connect(serverSocket, info->ai_addr, info->ai_addrlen);
        if (-1 == status) {
            continue;
        }

        break;
    }

    if (NULL == info) {
        if (-1 == serverSocket) {
            string message = "could not create socket: ";
            message += strerror(errno);

            throw ClientException(message, ClientException::CODE_SOCKET_ERROR);
        } else {
            throw ClientException("could not connect to host " + serverHost + ":" + serverPort + ": " + strerror(errno),
                                  ClientException::CODE_CONNECT_ERROR);
        }
    }
}

/**
 * Return all IPs in string representation.
 *
 * @return all ips separated by comma
 */
string Client::getServerAddress() {
    struct addrinfo *info;
    char ipString[INET6_ADDRSTRLEN];
    string result;

    for(info = serverInfo; NULL != info; info = info->ai_next) {
        void *address;

        if (AF_INET == info->ai_family) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) info->ai_addr;
            address = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) info->ai_addr;
            address = &(ipv6->sin6_addr);
        }

        inet_ntop(info->ai_family, address, ipString, sizeof ipString);

        result += ipString;
        if (NULL != info->ai_next) {
            result += ", ";
        }
    }

    return result;
}

/**
 * Initialize the server connectivity.
 */
void Client::init() {
    setServerInfo();
    connectToServer();
}

/**
 * Set the address info for the server.
 */
void Client::setServerInfo() {
    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(serverHost.c_str(), serverPort.c_str(), &hints, &serverInfo);
    if (0 != status) {
        string message = "failed to get server address info: ";
        message += gai_strerror(status);

        throw ClientException(message, ClientException::CODE_NO_SERVER_ADDRESS_INFO);
    }
}

/**
 * Close connection and free resources.
 */
void Client::shutdown() {
    freeaddrinfo(serverInfo);
    if (0 <= serverSocket) {
        close(serverSocket);
    }
}
