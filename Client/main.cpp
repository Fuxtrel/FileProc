#include <zmq.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <string>

int main() {
    std::cout << "Connection to server...\n";
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:4040");

    std::string auth[2];
    auth[0] = "login";
    auth[1] = "password";
    char buffer[128] = {'\0'};

    std::cout << "Sending login/password\n";
    zmq_send(socket, auth[0].c_str(), auth[0].length(), 0);
    zmq_recv(socket, buffer, 128, 0);
    std::string message;
    memcpy(buffer, message.c_str(), strlen(buffer));
    if(message == "login ok"){
        zmq_send(socket, auth[1].c_str(), auth[0].length(), 0);
    }

    /*for (int i = 0; i < 2; i++) {
        zmq_send(socket, auth[i].c_str(), 128, 0);
        zmq_recv(socket, buffer, 128, 0);
        memcpy(buffer, result[i], 128);
        for(int i = 0; i < 128; i++){
            buffer[i] = '\0';
        }
    }
    if(((std::string)result[0] == "login done") && ((std::string)result[0] == "password done")){
        zmq_send(socket, "Continue", 128, 0);
    }
    zmq_recv(socket, buffer, 128, 0);
    std::cout << std::string(buffer) << std::endl;
*/
    zmq_close(socket);
    zmq_ctx_destroy(context);
}