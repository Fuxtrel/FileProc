#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>

int main() {
    std::cout << "Connection to server...\n";
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:4040");

    char auth[2][128] = {"login", "password"};
    char buffer[128];

    std::cout << "Sending login/password\n";

    for (int i = 0; i < 2; i++) {
        zmq_send(socket, auth[i], 128, 0);
        zmq_recv(socket, buffer, 128, 0);
        std::cout << (std::string) buffer << std::endl;
    }


    zmq_close(socket);
    zmq_ctx_destroy(context);
}