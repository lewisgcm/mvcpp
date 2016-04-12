#pragma once

#include <cstring>
#include <cctype>
#include <stdio.h>

class StringRef {

    char* string_ptr_;
    int length_;

public:

    StringRef( char* string_ptr, int length );

    void trim();

    void to_lower();

    const char* c_str();
};