/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <time.h>

using namespace std;

namespace Log {

    /**
     * Log.
     * Log function is used to write a message to the log 
     * for the application. A time will be added but no error
     * name or location.
    */
    void Log( const char* message, ... );

    /**
     * Error.
     * Logs an error message into the log with time, file, line number and message
    */
    #define Error(M, ...) Log( "Error:%s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );

    /**
     * Warning.
     * Logs an warning message into the log with time, file, line number and message
    */
    #define Warning(M, ...) Log( "Warning:%s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );

    /**
     * Info.
     * Logs an info message into the log with time, file, line number and message
    */
    #define Info(M, ...) Log( "Info:%s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__ );
}