#include <QCoreApplication>
#include "websocketclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebSocketClient client;
    return QCoreApplication::exec();
}
