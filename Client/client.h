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


class Client{
public:
    Client();
};

void coolDown(void *socket);



#endif //FILEPROC_CLIENT_H
