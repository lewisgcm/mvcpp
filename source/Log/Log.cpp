/**
 * (c) Lewis Maitland 2015
*/
#include <Log/Log.hpp>

void Log::Log( const char* message, ... ) {

    time_t now = time(0);

    va_list arglist;

    char *t = ctime(&now);
    char *p = strchr(t, '\n');
    if( p != NULL ) {
        *p = ' ';
    }

    fprintf( stderr, "[%s]: ", t );
    va_start( arglist, message );
    vfprintf( stderr, message, arglist );
    va_end( arglist );
}