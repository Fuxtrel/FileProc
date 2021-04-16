#include <zmq.h>
#include <cstring>
#include <cassert>
#include <iostream>
#include "proxy.h"


/*
int main() {
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(socket, "tcp://*:4040");
    std::string msg;
    assert(rc == 0);
    char buffer[128] = {'\0'};
    while(true) {
    zmq_recv(socket, buffer, 128, 0);
        if ((std::string) buffer == "login") {
            Proxy px;
            msg = std::to_string(px.genUserID());
            msg += std::string(buffer);
            zmq_send(socket, "login ok", 8, 0);
            break;
        } else if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        } else {
            zmq_send(socket, "Authorisation denied", 20, 0);
            break;
        }
        memset(buffer, '\0', 128);
    }
    memset(buffer, '\0', 128);
    while(true) {
        zmq_recv(socket, buffer, 128, 0);
        if ((std::string) buffer == "password") {
            zmq_send(socket, "password ok", 11, 0);
            break;
        } else if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        }else {
            zmq_send(socket, "Authorisation denied", 20, 0);
            break;
        }
        memset(buffer, '\0', 128);
    }
    while(true) {
        memset(buffer, '\0', 128);
        zmq_recv(socket, buffer, 128, 0);
        if ((std::string) buffer == "Authentication done") {
            std::cout << "Authentication done\n";
            break;
        }else if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        }
    }
    zmq_send(socket, msg.c_str(), msg.length(), 0);
    while(true){
        memset(buffer, '\0', 128);
        zmq_recv(socket, buffer, 128, 0);
        if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        }else {
            std::string ip = std::string(buffer);
            zmq_send(socket, "ip_ok", 5, 0);
            break;
        }
    }
    while(true){
        memset(buffer, '\0', 128);
        zmq_recv(socket, buffer, 128, 0);
        if(std::string(buffer) == "UID_arendator"){
            zmq_send(socket, "ip, port", 8, 0);
            break;
        }else if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        }
    }

    /*while(true) {
        memset(buffer, '\0', 128);
        zmq_recv(socket, buffer, 128, 0);
        if ((std::string) buffer == "KAL") {
            zmq_send(socket, "KAL_OK", 6, 0);
        }
    }

}*/
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Echoes back all received WebSocket messages
void
do_session(tcp::socket socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

        // Accept the websocket handshake
        ws.accept();

        for(;;)
        {
            // This buffer will hold the incoming message
            beast::flat_buffer buffer;

            // Read a message
            ws.read(buffer);

            // Echo the message back
            ws.text(ws.got_text());
            ws.write(buffer.data());
        }
    }
    catch(beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------

int main()
{
    std::string argv1 = "5.18.95.96";
    std::string argv2 = "4040";
    try
    {
        auto const address = net::ip::make_address(argv1);
        auto const port = static_cast<unsigned short>(std::atoi(argv2.c_str()));

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc/*, {address, port}*/};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread(
                    &do_session,
                    std::move(socket)).detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
