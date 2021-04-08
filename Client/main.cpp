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