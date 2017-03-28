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
    string serverHost;
    struct addrinfo *serverInfo;
    string serverPort;
    int serverSocket;

    void connectToServer();
    void setServerInfo();

public:
    Client(const string host, const string port);
    void init();
    void shutdown();
    string getServerAddress();
};


#endif //MESPLE_CLIENT_CLIENT_HPP
