#include <Http/Server.hpp>

namespace Http {
    Server::Server( unsigned int port, std::string host, Routing::Router& router ) {
        this->port_   = port;
        this->router_ = router;

        //Determine size of thread pool and create mutex/pool
        unsigned int size = std::max( std::thread::hardware_concurrency() , (unsigned int)4 );
        for( unsigned int i = 0; i < size; i++ ) {
            pool_.push_back( new std::queue<tcp::iostream*>() );
            mutex_.push_back( new std::mutex() );
            std::thread (Server::threadHandler, pool_[i], mutex_[i], router ).detach();
        }
    }

    int Server::run() {
        tcp::acceptor acceptor( this->io_service_, tcp::endpoint(tcp::v4(), this->port_) );

        int current_worker = 0;
        int poolSize = this->pool_.size();
        while( 1 ) {
            tcp::iostream* stream = new tcp::iostream();
            acceptor.accept( *stream->rdbuf() );

            current_worker = (current_worker+1) % poolSize;
            this->mutex_[ current_worker ]->lock();
            this->pool_ [ current_worker ]->push( stream );
            this->mutex_[ current_worker ]->unlock();
        }
        return 0;
    }

    void Server::threadHandler( std::queue<tcp::iostream*>* pool, std::mutex* lock, Routing::Router router ) {
        while( true ) {
            lock->lock();
            if( pool->size() > 0 ) {
                tcp::iostream* stream = pool->front();
                pool->pop();

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
            lock->unlock();
            usleep( 5 );
        }
    }
}