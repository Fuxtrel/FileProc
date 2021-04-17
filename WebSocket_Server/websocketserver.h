#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QObject>
#include <iostream>

class WebSocketServer;

class WebSocketServer: public QObject{

    Q_OBJECT

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer() override;

signals:
    void closed();

private slots:
    void NewConnection();
    void ProcessTextMessage(const QString& message);
    void RecieveFile(const QByteArray& message);
    void SocketDisconnected();

private:
    QWebSocketServer *Web_socket_server;
    QList<QWebSocket *> clients;
    QWebSocket *aSocket;
    QString token;
    QString filename;
    int i = 0;
};

#endif // WEBSOCKETSERVER_H
