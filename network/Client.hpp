/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_CLIENT_CLIENT_HPP
#define MESPLE_CLIENT_CLIENT_HPP


#include <string>
#include <netdb.h>

using namespace std;

class Client {
private:
    struct addrinfo *serverInfo;
    string serverPort;
    string serverHost;

    void setServerInfo();

public:
    Client(const string host, const string port);
    void init();
    void shutdown();
};


#endif //MESPLE_CLIENT_CLIENT_HPP
