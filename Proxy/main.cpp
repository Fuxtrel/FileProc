#include <zmq.h>
#include <cstring>
#include <cassert>
#include <iostream>
#include "proxy.h"



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
    }*/

}