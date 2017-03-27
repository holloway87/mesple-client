/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <cstring>

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
 * Initialize the server connectivity.
 */
void Client::init() {
    setServerInfo();
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
}
