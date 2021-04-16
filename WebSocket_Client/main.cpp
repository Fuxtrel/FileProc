#include <QCoreApplication>
#include "websocketclient.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebSocketClient client;
    return QCoreApplication::exec();
}
