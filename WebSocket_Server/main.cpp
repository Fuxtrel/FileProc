#include <QCoreApplication>
#include <QWebSocket>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QThread>
#include <QObject>

#include <iostream>
#include <string>
#include "websocketserver.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //qDebug()<< "io";
    WebSocketServer server;
    return a.exec();

}
