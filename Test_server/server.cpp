#include "server.h"
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QThread>
#include <QFileInfo>



Server::Server(QObject *parent) : QObject(parent)
{
    packetType = PacketType::TYPE_NONE;
        filePath.clear();
        fileSize = 0;
        testStr.clear();
        sizeReceivedData = 0;
        tmpBlock.clear();
        countSend = 0;
        i =0;
        bufferPath = "../buffer.txt";

}
void Server::startServer()
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);
    // QThread::msleep(20000);
    if(!mTcpServer->listen(QHostAddress("0.0.0.0"),40901)) {
        qFatal("SERVER: server is not started");
    }
    //path = "/home/vladimir/Work/Test_server/";
    qDebug() << Tools::getTime() << "SERVER: server is started";
}

Server::~Server()
{
    qDebug() << "MyTcpServer::~MyTcpServer()";
    delete mTcpSocket;
    delete mTcpServer;
}

void Server::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    //qDebug() << "Client connected";
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    //connect(mTcpSocket, &QTcpSocket::readyRead, this, &Server::slotSendMessageFile);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
}


void Server::slotClientDisconnected()
{
    mTcpSocket->close();
}


void Server::slotReadyRead()

{

    if (!mTcpSocket || !mTcpSocket->bytesAvailable())
        return;

//    qDebug() << Tools::getTime() << "SERVER: --------------------new-----------------------";
//    qDebug() << Tools::getTime() << "SERVER: slotReadyRead(): bytesAvailable" << mTcpSocket->bytesAvailable();

    QDataStream stream(mTcpSocket);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        //====================================================
        // Получение filePath

        if (filePath.isEmpty()) {
            stream.startTransaction();
            stream >> filePath;
            //qDebug() << filePath;
            if (!stream.commitTransaction()) {
                //qDebug() << Tools::getTime() << "SERVER: filePath - FAIL commitTransaction";
                return;
            }
            //qDebug() << Tools::getTime() << "SERVER: filePath:" << filePath;

            if (filePath == "get.txt"){
                slotSendMessageFile();
                //qDebug() << "get seccessful";
            }

        //====================================================
        // Получение fileSize

        if (!fileSize) {
            stream.startTransaction();
            stream >> fileSize;
            if (!stream.commitTransaction()) {
                qDebug() << Tools::getTime() << "SERVER: fileSize - FAIL commitTransaction";
                return;
            }
            //qDebug() << Tools::getTime() << "SERVER: fileSize:" << fileSize;
        }

        //====================================================
        // Получение файла

        if (sizeReceivedData != fileSize)
        {
             // временная замена имени файла
            QString FilePath =bufferPath;
            QFile file(FilePath);
            file.open(QFile::WriteOnly);


                //====================================================
                // Получение tmpBlock

                stream.startTransaction();
                stream >> tmpBlock;
                //qDebug() << tmpBlock;


                qint64 toFile = file.write(tmpBlock);
                //                    qDebug() << Tools::getTime() << "SERVER: toFile    : " << toFile;

                sizeReceivedData += toFile;

                //                    qDebug() << Tools::getTime() << "SERVER: countSend: " << countSend;
                //                    qDebug() << Tools::getTime() << "SERVER: sizeReceivedData: " << sizeReceivedData;
                //                    qDebug() << Tools::getTime() << "SERVER: -------------------------------------------------" << endl;

                tmpBlock.clear();

                if (sizeReceivedData == fileSize) {
                    //qDebug() << Tools::getTime() << "SERVER: sizeReceivedData END: " << sizeReceivedData;
                    //qDebug() << Tools::getTime() << "SERVER fileSize ORIG:" << fileSize;
                    //qDebug() << Tools::getTime() << "SERVER: countSend FINAL: " << countSend;
                    //break;
                }

            //}

            file.close();

        //qDebug() << Tools::getTime() << "SERVER: END - bytesAvailable:" << mTcpSocket->bytesAvailable();

        // Очистка переменных

    } // else if (packetType == PacketType::TYPE_FILE)



    //exit(0);

    }

        filePath.clear();
    packetType = PacketType::TYPE_NONE;
    fileSize = 0;
    tmpBlock.clear();
    sizeReceivedData = 0;
    countSend = 0;
}

void Server::slotSendMessageFile()
{
    //qDebug() << "STarting transmission";
    //qDebug() << "Socket state:" << (mTcpSocket == nTcpSocket);
    QDataStream stream(mTcpSocket);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    //stream << PacketType::TYPE_FILE;

    QString fileName =bufferPath;
    //qDebug() << fileName;

    //stream << fileName << fileSize;
    //qDebug() << stream;
    //mTcpSocket->waitForBytesWritten();
    //qDebug() << Tools::getTime() << "_CLIENT: fileSize";

    sendFile = new QFile(fileName);

    if(sendFile->open(QFile::ReadOnly)) {
        QFile file(fileName);
        QFileInfo fileInfo(file);
        fileSize = fileInfo.size();
        //connect(mTcpSocket, &QTcpSocket::bytesWritten, this, &Server::sendPartOfFile);
        //connect(this, &Client::endSendFile, this, &Client::slotEndSendFile);
        QDataStream stream(mTcpSocket);
        stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

            QByteArray data = sendFile->readAll();
            //QByteArray data = sendFile->read(1024*1000*10);
            //qDebug() << data;
            stream << data;
            //qDebug() << stream;
            //qDebug() << Tools::getTime() << "_CLIENT: slot sendPartOfFile() | File end!";
            sendFile->close();
            sendFile = NULL;
    } else {
        qFatal("_CLIENT: File not open!");
    }
    fileName.clear();
}

