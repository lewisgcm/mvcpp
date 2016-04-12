#pragma once

#include <string>
#include <Helper/StringRef.hpp>

using namespace std;

class StringSplitter {

    int size_;
    int max_size_;
    char* memory_;
    StringRef* results_;

public:

    StringSplitter( int max_size = 100 );

    void split( const string &str, const char *delimiters );

    StringRef* results();

    int size();

    ~StringSplitter();
};
