#include "mytcpserver.h"
#include "functions.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    TCPServer->close();
    server_status = 0;
}

MyTcpServer::MyTcpServer()
{
    TCPServer = new QTcpServer(this);
    connect(TCPServer, &QTcpServer::newConnection,
            this, &MyTcpServer::NewConnection);

    if(!TCPServer->listen(QHostAddress::Any, 33333))
    {
        qDebug() << "Error. Server is not started";
    } else {
        server_status = 1;
        qDebug() << "Server is started";
    }
}

void MyTcpServer::NewConnection()
{
    if(server_status == 1)
    {
        qDebug() << "New client connected";
        QTcpSocket *Current_TCPSocket;
        Current_TCPSocket = TCPServer->nextPendingConnection();
        Current_TCPSocket->write("Hello, World!!! I am EduTest Server!\r\n");
        long long connection_id = Current_TCPSocket->socketDescriptor();
        Current_TCPSocket->write("Your connection ID: ");
        Current_TCPSocket->write(QString::number(connection_id).toUtf8());
        Current_TCPSocket->write("\r\n");
        Clients.insert(Current_TCPSocket,connection_id);
        connect(Current_TCPSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::ServerDataRead);
        connect(Current_TCPSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::ClientDisconnected);
    }
}

void MyTcpServer::ServerDataRead()
{
    QTcpSocket *Current_TCPSocket = (QTcpSocket*)sender();
    QByteArray data_output;
    QString data_input;
    while(Current_TCPSocket->bytesAvailable()>0)
    {
        data_input += Current_TCPSocket->readAll();
    }
    QString connection_id = QString::number(Current_TCPSocket->socketDescriptor());
    data_output = parsing(data_input, connection_id).toUtf8();
    Current_TCPSocket->write(data_output);
}

void MyTcpServer::ClientDisconnected()
{
    QTcpSocket *Current_TCPSocket = (QTcpSocket*)sender();
    qDebug() << "Client disconnected";
    QString connection_id = QString::number(Clients.value(Current_TCPSocket));
    close_session(connection_id);
    Clients.remove(Current_TCPSocket);
    Current_TCPSocket->close();
}
