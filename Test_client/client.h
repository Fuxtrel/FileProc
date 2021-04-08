#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QSslSocket>
#include "global.h"
#include <QFile>


class Client : public QObject
{
    Q_OBJECT

public:
    Client(char *argv[], QString path);
    ~Client();

private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;
    int countSend;
    qint64 fileSize;
    qint64 sizeSendData;
    QFile *sendFile;
    QString serverHost;
    QString path;
    QString filename;
    QString senderID;
    QStringList list;
    QString getterID;
    QString fileNameInDirectory;
    quint16 serverPort;
    void sendPartOfFile();
    void ReadFile();

    QTcpSocket *mTcpSocket;
    qint64 sizeReceivedData;
    QString fileCopy;
    QString filePath;
    QString testStr;
    QByteArray tmpBlock;


signals:
    void disconnected(void);
    void endSendFile();

private slots:
    void slotReadyRead ();
    void slotError (QAbstractSocket::SocketError);
    void slotConnected ();
    void slotDisconnected();
    void socketSendFile();




public slots:
    void startClient();
};
#endif // CLIENT_H
