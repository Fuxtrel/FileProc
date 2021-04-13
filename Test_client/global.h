#ifndef GLOBAL_H
#define GLOBAL_H


#include <QString>

#define TCP_READ_TIMEOUT 5000

enum PacketType
{
    TYPE_NONE = 0,
    TYPE_FILE = 1,
};


class Tools {
public:
    static void printTime();
    static QString getTime();
};



#endif // GLOBAL_H
