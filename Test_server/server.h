#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QObject>
#include "global.h"
#include <QFile>

class Server : public QObject
{
    Q_OBJECT
public:
     Server(QObject *parent = 0);
    ~Server();
public slots:
    void startServer();

private slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotReadyRead();
    void slotSendMessageFile();

private:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
    QTcpSocket *nTcpSocket;
    quint16 serverPort;
    qint64 sizeReceivedData;
    QString fileCopy; // Путь файла для сохранение
    QString path;
    QString fileP = "/home/vladimir/Work/Test_server/";
    PacketType packetType;
    QString bufferPath;

    QString filePath;
    qint64 fileSize;
    QString testStr;
    QByteArray tmpBlock;
    int countSend;
        int i;
    qint64 sizeSendData;
    QFile *sendFile;
    QString serverHost;
    void sendPartOfFile();
};

#endif // SERVER_H
