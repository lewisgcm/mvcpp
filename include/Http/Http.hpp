/**
 * (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

namespace Http {

    /*Type definition for cleaner cpp code*/
    typedef map<string, string> HttpHeaders;

    /*Constants for HTTP/Application configuration*/
    const unsigned int MAX_REQUEST_LINE_LENGTH = 2048;
    const unsigned int MAX_REQUEST_BODY_LENGTH = 2048;
    const unsigned int MAX_REQUEST_TIMEOUT     = 120;
    const HttpHeaders  DEFAULT_SERVER_HEADERS  = {
        { "server",          "MVC++ v0.1a" },
        { "content-type",    "text/plain" },
        { "x-frame-options", "SAMEORIGIN"}
    };

    /*HTTP Constant enumeration types*/
    enum HttpMethod  { GET, POST, PUT, DELETE, HEAD, TRACE };
    enum HttpVersion { HTTP_9 , HTTP1_0 , HTTP1_1 , HTTP2_0 };
    enum HttpStatus  {
        OK                    = 200,
        CREATED               = 201,
        BAD_REQUEST           = 400,
        NOT_FOUND             = 404,
        INTERNAL_SERVER_ERROR = 500
    };

    /*HTTP Constant enumeration string type mappings*/
    const std::vector<string> HttpMethodString  = { "GET", "POST", "PUT", "DELETE", "HEAD", "TRACE" };
    const std::vector<string> HttpVersionString = { "HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0" };
    const std::map< HttpStatus, const string > HttpResponseStrings = {
        { OK,                    "Ok" },
        { BAD_REQUEST,           "Bad Request" },
        { NOT_FOUND,             "Not Found" },
        { INTERNAL_SERVER_ERROR, "Internal Server Error" }
    };

    /**
     * --------------------------
     * +   Http status codes    +
     * --------------------------
     * 100 - "Continue",
     * 101 - "Switching Protocols",
     * 102 - "Processing",
     * 200 - "OK",
     * 201 - "Created",
     * 202 - "Accepted",
     * 203 - "Non-Authoritative Information",
     * 204 - "No Content",
     * 205 - "Reset Content",
     * 206 - "Partial Content",
     * 207 - "Multi-Status",
     * 300 - "Multiple Choices",
     * 301 - "Moved Permanently",
     * 302 - "Found",
     * 303 - "See Other",
     * 304 - "Not Modified",
     * 305 - "Use Proxy",
     * 306 - "Switch Proxy",
     * 307 - "Temporary Redirect",
     * 400 - "Bad Request",
     * 401 - "Unauthorized",
     * 402 - "Payment Required",
     * 403 - "Forbidden",
     * 404 - "Not Found",
     * 405 - "Method Not Allowed",
     * 406 - "Not Acceptable",
     * 407 - "Proxy Authentication Required",
     * 408 - "Request Timeout",
     * 409 - "Conflict",
     * 410 - "Gone",
     * 411 - "Length Required",
     * 412 - "Precondition Failed",
     * 413 - "Request Entity Too Large",
     * 414 - "Request-URI Too Long",
     * 415 - "Unsupported Media Type",
     * 416 - "Requested Range Not Satisfiable",
     * 417 - "Expectation Failed",
     * 418 - "I\"m a teapot",
     * 422 - "Unprocessable Entity",
     * 423 - "Locked",
     * 424 - "Failed Dependency",
     * 425 - "Unordered Collection",
     * 426 - "Upgrade Required",
     * 449 - "Retry With",
     * 450 - "Blocked by Windows Parental Controls",
     * 500 - "Internal Server Error",
     * 501 - "Not Implemented",
     * 502 - "Bad Gateway",
     * 503 - "Service Unavailable",
     * 504 - "Gateway Timeout",
     * 505 - "HTTP Version Not Supported",
     * 506 - "Variant Also Negotiates",
     * 507 - "Insufficient Storage",
     * 509 - "Bandwidth Limit Exceeded",
     * 510 - "Not Extended"
    */
}