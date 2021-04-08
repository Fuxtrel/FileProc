#include <QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QThread>
#include <QObject>

#include <iostream>
#include <string>
#include "server.h"
using namespace std;

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  Server *server = new Server();
  QThread *threadServer = new QThread;
      QObject::connect(threadServer, &QThread::started, server, &Server::startServer);
      QObject::connect(threadServer, &QThread::finished, server, &Server::deleteLater);
      server->moveToThread(threadServer);
      threadServer->start();
  return app.exec();
}
