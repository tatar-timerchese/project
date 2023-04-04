#ifndef FUNC_SERVER_H
#define FUNC_SERVER_H
#include <QObject>


void Parsing(QByteArray message);
void Login(QString username, QString password);
void Registration(QString email,QString username, QString password);
void CheckResult(); 
void Statistic_stud();
void Statistic_teach();
#endif // FUNC_SERVER_H
