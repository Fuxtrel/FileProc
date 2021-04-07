#include "client.h"


void foo(void *socket) {
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

}


int main() {
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:4040");
    std::thread client(foo, socket);
    for(int i = 0; i < 5; i++) {
        std::thread timer(coolDown, socket);
        timer.join();
    }
    zmq_close(socket);
    zmq_ctx_destroy(context);
    client.join();


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
    zmq_ctx_destroy(context);*/
}