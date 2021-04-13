#ifndef FILEPROC_CLIENT_H
#define FILEPROC_CLIENT_H

#include <cstring>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "client.h"
#include <unistd.h>
#include <mutex>
#include <zmq.h>



void coolDown(void *socket);

class Client{
public:
    Client();
    std::string getIP();
    bool authorization();
};


class Token{
public:
    Token();

    ~Token();
};



#endif //FILEPROC_CLIENT_H
