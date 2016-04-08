#include <Http/Server.hpp>

namespace Http {

    Server::Server( unsigned int port, std::string host ) {
        this->port_ = port;
    }

    int Server::run( Routing::Router& router, Routing::ControllerErrorAction onError ) {
        tcp::acceptor acceptor( this->io_service_, tcp::endpoint(tcp::v4(), this->port_) );

        while( 1 ) {
            tcp::iostream* stream = new tcp::iostream();
            acceptor.accept( *stream->rdbuf() );
            std::thread (Server::threadHandler, stream, router, onError ).detach();
        }
        return 0;
    }

    int Server::run( Routing::ControllerAction onAccept, Routing::ControllerErrorAction onError ) {

        tcp::acceptor acceptor( this->io_service_, tcp::endpoint(tcp::v4(), this->port_) );

        while( 1 ) {
            tcp::iostream* stream = new tcp::iostream();
            acceptor.accept( *stream->rdbuf() );

            std::thread ( []( Routing::ControllerAction onAccept, Routing::ControllerErrorAction onError, tcp::iostream* stream ){

                try { 
                    Http::Request  request( *stream );
                    Http::Response response( Http::HTTP1_1, { { "Server", "MVC++ Server" } }, *stream );
                    onAccept( request, response );
                } catch( ... ) {
                    Http::Response response( Http::HTTP1_1, { { "Server", "MVC++ Server" } }, *stream );
                    onError( response, std::current_exception() );
                }

                delete stream;
            }, onAccept, onError, stream ).detach();
        }
    }

    void Server::threadHandler( tcp::iostream* stream, Routing::Router router, Routing::ControllerErrorAction onError ) {
        try {
            stream->expires_from_now( boost::posix_time::seconds( Http::MAX_REQUEST_TIMEOUT ) );
            Http::Request  request( *stream );
            Http::Response response( Http::HTTP1_1, {
                { "Server", "MVC++ Server" }
            }, *stream );

            router.handleRequest( request, response );
        } catch( ... ) {
            Http::Response response( Http::HTTP1_1, { { "Server", "MVC++ Server" } }, *stream );
            onError( response, std::current_exception() );
        }
        delete stream;
    }
}