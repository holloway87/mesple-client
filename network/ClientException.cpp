/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include "ClientException.hpp"

/**
 * New instance with the given message and code.
 *
 * @param message
 * @param code
 */
ClientException::ClientException(const string message, const short code) {
    this->message = message;
    this->code = code;
}
