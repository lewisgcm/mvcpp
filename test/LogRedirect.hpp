#pragma once

#include <cstdio>

#define REDIRECT_ON(M) if( std::freopen( "test_stderr.txt","w", M ) == NULL ) fprintf( stderr, "Could not redirect." );
#define REDIRECT_OFF(M) fclose(M);