/*
#include "client.h"


void foo(void *socket, std::string ip) {
    std::cout << "Connection to server...\n";


    std::string auth[2];
    auth[0] = "login";
    auth[1] = "password";
    bool authentication[2] = {false};
    char buffer[128] = {'\0'};

    std::cout << "Sending login/password\n";
    zmq_send(socket, auth[0].c_str(), auth[0].length(), 0);
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    if ((std::string) buffer == "login ok") {
        authentication[0] = true;
        zmq_send(socket, auth[1].c_str(), auth[1].length(), 0);
    }
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);

    if ((std::string) buffer == "password ok") {
        authentication[0] = true;
        zmq_send(socket, "Authentication done", 19, 0);
    }
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    std::cout << std::string(buffer) << std::endl;
    //Отсылаем свой ip
    zmq_send(socket, ip.c_str(), 11, 0);

    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    if ((std::string) buffer != "ip_ok") {
        zmq_send(socket, "ip not correct", 14, 0);
    }
    zmq_send(socket, "UID_arendator", 13, 0);
    std::string ip_arendator;
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    ip_arendator = std::string(buffer);
    std::cout << ip_arendator << std::endl;

}


int main(int argc, char* argv[]) {
    std::string ip = std::string(argv[1]);
    std::cout << ip << std::endl;
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:4040");
    std::thread client(foo, socket, ip);
    /*for(int i = 0; i < 5; i++) {
        std::thread timer(coolDown, socket);
        timer.join();
    }*/
    client.join();
    zmq_close(socket);
    zmq_ctx_destroy(context);



    */
/*std::cout << "Connection to server...\n";
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:4040");

    std::string auth[2];
    auth[0] = "login";
    auth[1] = "password";
    bool authentication[2] = {false};
    char buffer[128] = {'\0'};

    std::cout << "Sending login/password\n";
    zmq_send(socket, auth[0].c_str(), auth[0].length(), 0);
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    if((std::string)buffer == "login ok"){
        authentication[0] = true;
        zmq_send(socket, auth[1].c_str(), auth[1].length(), 0);
    }
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);

    if((std::string)buffer == "password ok"){
        authentication[0] = true;
        zmq_send(socket, "Authentication done", 19, 0);
    }
    memset(buffer, '\0', 128);
    zmq_recv(socket, buffer, 128, 0);
    std::cout << std::string(buffer) << std::endl;

    //Start timer


    zmq_close(socket);
    zmq_ctx_destroy(context);*//*

}

//
//*/


//[example_websocket_client

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Sends a WebSocket message and prints the response
int main()
{

    try
    {
        std::string host = "5.18.95.96";
        auto const  port = "4040";
        auto const  text = "test message";

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        auto ep = net::connect(ws.next_layer(), results);

        // Update the host_ string. This will provide the value of the
        // Host HTTP header during the WebSocket handshake.
        // See https://tools.ietf.org/html/rfc7230#section-5.4
        host += ':' + std::to_string(ep.port());

        // Set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
                [](websocket::request_type& req)
                {
                    req.set(http::field::user_agent,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-client-coro");
                }));

        // Perform the websocket handshake
        ws.handshake(host, "/");

        // Send the message
        ws.write(net::buffer(std::string(text)));

        // This buffer will hold the incoming message
        beast::flat_buffer buffer;

        // Read a message into our buffer
        ws.read(buffer);

        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);

        // If we get here then the connection is closed gracefully

        // The make_printable() function helps print a ConstBufferSequence
        std::cout << beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}