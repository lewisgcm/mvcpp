#include <Http/Server.hpp>

namespace Http {
    Server::Server( unsigned int port, std::string host, Routing::Router& router ) {
        this->port_   = port;
        this->router_ = router;
    }

    int Server::run() {
        tcp::acceptor acceptor( this->io_service_, tcp::endpoint(tcp::v4(), this->port_) );

        while( 1 ) {
            tcp::iostream* stream = new tcp::iostream();
            acceptor.accept( *stream->rdbuf() );
            std::thread (Server::threadHandler, stream, this->router_ ).detach();
        }
        return 0;
    }

    void Server::threadHandler( tcp::iostream* stream, Routing::Router router ) {
        try {
            Http::Request  request( *stream );
            Http::Response response( Http::HTTP1_1, {
                { "Content-type", "application/json" }
            }, *stream );
            router.handleRequest( request, response );
        } catch( ... ) {
            Http::Response response( Http::HTTP1_1, {}, *stream );
            *stream << "Error";
            response.send( Http::INTERNAL_SERVER_ERROR );
        }
        delete stream;
    }
}