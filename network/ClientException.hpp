/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#ifndef MESPLE_CLIENT_CLIENTEXCEPTION_HPP
#define MESPLE_CLIENT_CLIENTEXCEPTION_HPP


#include <string>

using namespace std;

class ClientException {
public:
    const static short CODE_NO_SERVER_ADDRESS_INFO = 10;
    const static short CODE_SOCKET_ERROR = 11;
    const static short CODE_CONNECT_ERROR = 12;

    short code;
    string message;

    ClientException(const string message, const short code);
};


#endif //MESPLE_CLIENT_CLIENTEXCEPTION_HPP
