/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <exception>
#include <string>

using namespace std;

namespace Exception {

    /**
     * Exception.
     * Exception class extends exception base class but provides an
     * error message. File, line and message can also be added to the
     * exception.
    */
    class Exception : public exception {
    protected:
        string message;

    public:

        /**
         * Constructor.
         * Connstructor takes a message for the exception.
         * @param[in] message Message of the exception.
        */
        Exception( string message );

        /**
         * getMessage.
         * Gets the message from the exception.
         * @return Returns the message from the exception.
        */
        string getMessage();
    };
}