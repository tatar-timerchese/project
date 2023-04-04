#include "Func_server.h"
#include <QDebug>
#include <QCoreApplication>


void Login(QString username, QString password){
    qDebug()<<"User= "<<username<<" pass="<<password;
}
void Registration(QString email,QString username, QString password){
 qDebug()<<"Mail= "<<email<<" name="<<username<<" pass="<<password;
}
void Parsing(QByteArray message){
    QList<QByteArray> parts = message.split('$');
        qDebug()<<parts[0];
        if(parts[0]=="login"){
            if (parts.count()!=3){
                qDebug()<<"Unvalid data for "<<parts[0];
            }
            else{
            QString name = parts[1];
            QString pass= parts[2];
            Login(name,pass);
            }
        }
        else if (parts[0]=="registration"){
            if (parts.count()!=4){
                qDebug()<<"Unvalid data for "<<parts[0];
            }
            else
            {
            QString mail=parts[1];
            QString name = parts[2];
            QString pass= parts[3];
            Registration(mail,name,pass);
            }
        }
        else{
            qDebug()<< "Invalid func name";
        }
    }
