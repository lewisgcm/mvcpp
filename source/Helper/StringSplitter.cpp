#include <Helper/StringSplitter.hpp>

    StringSplitter::StringSplitter( int max_size ) {
        max_size_ = max_size;
        results_ = (StringRef*)malloc( sizeof(StringRef*) * max_size );
    };

    void StringSplitter::split( char *str, const char *delimiters ) {
        char *saveptr;
        char *token;

        char* memory_ = str;
        //memory_ = (char*)malloc(str.length() + 1);
        //strcpy(memory_, str.c_str());

        size_ = 0;
        for(token = strtok_r(memory_, delimiters, &saveptr);
            token != NULL;
            token = strtok_r(NULL, delimiters, &saveptr)) {
            results_[ size_++ ] = StringRef( token, 20 );
        }
    }

    StringRef* StringSplitter::results() {
        return results_;
    }

    int StringSplitter::size() {
        return size_;
    }

    StringSplitter::~StringSplitter() {
        free( results_ );
        //free( memory_ );
    }