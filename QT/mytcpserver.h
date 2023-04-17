#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QMap>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer();
    ~MyTcpServer();
public slots:
    void NewConnection();
    void ClientDisconnected();
    void ServerDataRead();
private:
    QTcpServer *TCPServer;
    QMap<QTcpSocket*, long long> Clients;
    int server_status;
};

#endif // MYTCPSERVER_H
