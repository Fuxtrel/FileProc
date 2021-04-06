#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>

int main() {
    //  Socket to talk to clients
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(socket, "tcp://*:4040");
    assert(rc == 0);
    while (1) {
        //char buffer [100] = {'\0'};
        for (int i = 0; i < 2; i++) {
            char buffer[128] = {'\0'};
            zmq_recv(socket, buffer, 128, 0);
            if (std::string(buffer) == "login") {
                zmq_send(socket, "login done", 128, 0);
            } else {
                zmq_send(socket, "login denied", 128, 0);
            }
            if (std::string(buffer) == "password") {
                zmq_send(socket, "password done", 128, 0);
            } else {
                zmq_send(socket, "login denied", 128, 0);
            }
            sleep(1);
        }          //  Do some 'work'
        //zmq_send (socket, answer, answer.length(), 0);
    }
}