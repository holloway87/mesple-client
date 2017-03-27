/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <iostream>

#include "network/Client.hpp"
#include "network/ClientException.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (3 > argc) {
        cerr << "error: no host and port provided via parameters" << endl;

        return 1;
    }

    Client client {argv[1], argv[2]};

    try {
        client.init();
    } catch (ClientException e) {
        cerr << "error: " << e.message << endl;

        return e.code;
    }

    cout << "server address: " <<  client.getServerAddress() << endl;

    client.shutdown();

    return 0;
}
