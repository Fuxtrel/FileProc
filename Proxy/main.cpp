#include <zmq.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <iostream>
#include "proxy.h"



int main() {
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(socket, "tcp://*:4040");
    assert(rc == 0);
    char buffer[128] = {'\0'};
    zmq_recv(socket, buffer, 128, 0);
    std::string message;
    memcpy(buffer, message.c_str(), strlen(buffer));
    //Очистили буфер
    memset(buffer, '\0', 128);
    if(message == "login"){
        zmq_send(socket, "login ok", 8, 0);
    }else{
        zmq_send(socket, "Authorisation denied", 20, 0);
    }
    zmq_recv(socket, buffer, 128, 0);
    message.clear();
    memcpy(buffer, message.c_str(), strlen(buffer));
    if(message == "password"){
        zmq_send(socket, "password ok", 11, 0);
    }else{
        zmq_send(socket, "Authorisation denied", 20, 0);
    }

}