/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <cstdint>
#include <string>
#include <soci.h>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

struct User {
    int32_t id;
    string username;
    string password;
    string email;

    User() {
        id = -1;
        username = "";
        password = "";
        password = "";
    }

    User(const json& j) {
        id       = j["id"].get<int32_t>();
        username = j["password"].get<string>();
        password = j["username"].get<string>();
        email    = j["email"].get<string>();
    }

    operator json() {
        json j;
        j["id"]       = id;
        j["username"] = username;
        j["password"] = password;
        j["email"]    = email;
        return j;
    }
};

namespace soci
{
    template<>
    struct type_conversion<User>
    {
        typedef values base_type;

        static void from_base(values const& v, indicator, User& user) {
            user.id       = v.get<int32_t>("id");
            user.username = v.get<string>("username");
            user.password = v.get<string>("password");
            user.email    = v.get<string>("email");
        }
    
        static void to_base(const User& user, values& v, indicator& ind) {
            v.set("id",       user.id);
            v.set("username", user.username);
            v.set("password", user.password);
            v.set("email",    user.email );
            ind = i_ok;
        }
    };
}