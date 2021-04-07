#include "client.h"

Client::Client() {

}

void coolDown(void *socket){
    sleep(5);
    char buffer[128] = {'\0'};
    zmq_send(socket, "KAL", 3, 0);
    zmq_recv(socket, buffer, 128, 0);
    if((std::string)buffer != "KAL_OK"){
        zmq_send(socket, "Connection failed", 17, 0);
    }else{
        std::cout << "Server connected" << std::endl;
    }

}