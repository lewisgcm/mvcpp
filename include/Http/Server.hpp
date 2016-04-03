#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <queue>
#include <algorithm>
#include <Routing/Router.hpp>
#include <Log/Log.hpp>

using boost::asio::ip::tcp;

namespace Http {

    class Server {

        unsigned int port_;
        boost::asio::io_service io_service_;
        Routing::Router router_;
        std::vector< std::queue<tcp::iostream*>* > pool_;
        std::vector< std::mutex* > mutex_;

    public:
        Server( unsigned int port, std::string host, Routing::Router& router );
        int run();
    private:
        static void threadHandler( std::queue<tcp::iostream*>* pool, std::mutex* lock, Routing::Router router );
    };
}