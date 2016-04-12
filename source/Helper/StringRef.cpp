#include <Helper/StringRef.hpp>

StringRef::StringRef( char* string_ptr, int length ) {
    string_ptr_ = string_ptr;
    length_ = length;
}

void StringRef::trim() {
    char * p = string_ptr_;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(string_ptr_, p, l + 1);
}

void StringRef::to_lower() {
    char *p = string_ptr_;
    int l = strlen( p );
    while(*p) {
        if( !islower(*p) ) {
            *p = tolower(*p);
        }
        p++;
    }
}

const char* StringRef::c_str() {
    return (const char*) string_ptr_;
}