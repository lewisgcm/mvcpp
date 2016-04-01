/**
 * (c) Lewis Maitland 2015
*/
#include <Exception/Exception.hpp>

namespace Exception {
    Exception::Exception( string message ) {
        this->message = message;
    }

    string Exception::getMessage() {
        return this->message;
    }
}