#include "mytcpserver.h"
#include "Func_server.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{}
MyTcpServer::MyTcpServer(){
    if(this->listen(QHostAddress::Any,33333))//Задаём адреса и порт подключения к серверу
    {
        qDebug() << "start";
    }
    else    {
        qDebug() << "error";
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor){
    socket=new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead,this, &MyTcpServer::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug()<<"Client connected" <<socketDescriptor;
}

void MyTcpServer::slotReadyRead(){
    socket=(QTcpSocket*)sender();
    QDataStream in(socket);

    if(in.status()==QDataStream::Ok){
        qDebug() <<"Ready to read.";
        QByteArray requestData="";
        QString request = "";
        while(socket->bytesAvailable()>0){
        requestData = socket->readAll();;
        request += QString::fromUtf8(requestData);
        qDebug() <<"client said "<<request;
        }
        Parsing(requestData);
    }
    else{
        qDebug() << "DataStream error";
    }
}
void MyTcpServer::SendToClient(QString request){
    qDebug() <<"Sending... "<<request;
    data.clear();

    if (request=="who\r\n") {
        socket->write("cares\n");
    }
    
    else {
    QByteArray responseData= request.toUtf8();
    socket->write("You said: " +responseData);}
    socket->flush();
}
