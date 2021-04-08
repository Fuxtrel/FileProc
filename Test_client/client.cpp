#include <QSslKey>
#include <QSslCertificate>
#include "client.h"
#include <QDataStream>
#include <QThread>
#include <QFileInfo>


Client::Client(char *argv[], QString path)
{
    QTextStream cout(stdout);
    QTextStream cin(stdin);
    qDebug() << Tools::getTime() << "_CLIENT: TcpClient::TcpClient()";
    m_nNextBlockSize = 0;
    countSend = 0;
    sizeSendData = 0;
    fileSize = 0;
    cin >> filename;
    startClient();
    senderID = argv[0];
    getterID = argv[1];

    QStringList list= filename.split("/");
    QStringListIterator it(list);
    while (it.hasNext()) {
        fileNameInDirectory = it.next();
    }
}

Client::~Client()
{
    qDebug() << "TcpClient::~TcpClient()";
    delete m_pTcpSocket;
    delete sendFile;
}

void Client::startClient()
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(QHostAddress("0.0.0.0"),40901);

    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(disconnected()), SLOT(slotDisconnected()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void Client::slotConnected()
{
    //m_pTcpSocket-> write("sample text");
    this->socketSendFile();

}

void Client::slotDisconnected()
{
    qDebug() << "_CLIENT: slotDisconnected";
    m_pTcpSocket->close();
}

void Client::slotReadyRead()
{
    //qDebug() << "_CLIENT:" << m_pTcpSocket->readAll();
    if(fileNameInDirectory == "get.txt")
    {
        //qDebug() << "sample text";
        ReadFile();
    }
}


void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    qDebug() << "Link::slotError:" << strError;
}

void Client::socketSendFile()
{
    QDataStream stream(m_pTcpSocket);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    stream << PacketType::TYPE_FILE;
    QString fileName=filename;
    QFile file(fileName);
    QFileInfo fileInfo(file);
    fileSize = fileInfo.size();
    stream << fileNameInDirectory << fileSize;
    m_pTcpSocket->waitForBytesWritten();
    //qDebug() << Tools::getTime() << "_CLIENT: fileSize";

    sendFile = new QFile(fileName);
    //filePath.clear();
    if(sendFile->open(QFile::ReadOnly)) {
        sendPartOfFile();
    } else {

        qFatal("_CLIENT: File could not be opened!");
    }
}

void Client::sendPartOfFile()
{
    //QThread::msleep(200);

    QDataStream stream(m_pTcpSocket);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        QByteArray data = sendFile->readAll();
        //QByteArray data = sendFile->read(1024*100000);
        //qDebug() << data;
        stream << data;
        //qDebug() << Tools::getTime() << "_CLIENT: slot sendPartOfFile() | File end!";
        sendFile->close();
        sendFile = NULL;


}

void Client::ReadFile()
{

    this->fileCopy = filename;//"/home/vladimir/Work/Test_client/test_copy.txt"; пример пути к файлу
    if (QFile::exists(this->fileCopy))
        if (!QFile::remove(this->fileCopy))
            qFatal("File couldnt'd be removed!");


    QDataStream stream(m_pTcpSocket);
    stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        //====================================================
        // Получение filePath

        /*if (filePath.isEmpty()) {
            stream.startTransaction();
            stream >> filePath;
            if (!stream.commitTransaction()) {
                qDebug() << Tools::getTime() << "SERVER: filePath - FAIL commitTransaction";
                return;
            }
            qDebug() << Tools::getTime() << "SERVER: filePath:" << filePath;
        */


        //====================================================
        // Получение fileSize

        /*if (!fileSize) {
            stream.startTransaction();
            stream >> fileSize;
            if (!stream.commitTransaction()) {
                qDebug() << Tools::getTime() << "SERVER: fileSize - FAIL commitTransaction";
                return;
            }
            qDebug() << Tools::getTime() << "SERVER: fileSize:" << fileSize;
        }
        */

        //====================================================
        // Получение файла


            // временная замена имени файла

            QFile file(filename);
            file.open(QFile::WriteOnly);
            stream.startTransaction();
            stream >> tmpBlock;
            //qDebug() << tmpBlock;
            qint64 toFile = file.write(tmpBlock);
            //qDebug() << Tools::getTime() << "SERVER: toFile    : " << toFile;
            sizeReceivedData += toFile;
            //qDebug() << Tools::getTime() << "SERVER: countSend: " << countSend;
            //qDebug() << Tools::getTime() << "SERVER: sizeReceivedData: " << sizeReceivedData;
            //qDebug() << Tools::getTime() << "SERVER: -------------------------------------------------" << endl;
            tmpBlock.clear();

                /*if (sizeReceivedData == fileSize) {
                    qDebug() << Tools::getTime() << "SERVER: sizeReceivedData END: " << sizeReceivedData;
                    qDebug() << Tools::getTime() << "SERVER fileSize ORIG:" << fileSize;
                    qDebug() << Tools::getTime() << "SERVER: countSend FINAL: " << countSend;
                    //break;
                }*/

            //}

            file.close();

        /*if (sizeReceivedData != fileSize)
        {
            return;
        }*/


        // Очистка переменных
        filePath.clear();
        fileSize = 0;
        tmpBlock.clear();
        sizeReceivedData = 0;
        testStr.clear();
        countSend = 0;

}



