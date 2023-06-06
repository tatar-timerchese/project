#include "functions.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QVector>
#include <queue>

QByteArray parse(QString str){
    QStringList params = str.split("|");   
    qDebug()<<params[0];
    QString mail=params[1];          
    QString pass= params[2];
    QString verpass=params[3];
    QString role = params[4];
    if (params[0] =="auth"){
        if (params.count()!=3){
            qDebug();
             return "Invalid data for auth";
         }
         else{
            return auth(mail,pass);
         }
    }
    else if (params[0] =="rege"){
        if (params.count()!=5)
            return "Invalid data for registration";
        else{
            return rege(mail,role,pass,verpass);
        }
   }
   else if (params[0] == "stat"){
     if (params.count()!=2)
            return "Invalid data for statistics";
        else{
             stat(mail);
        }
   }
   else if (params[0] == "task1"){
      if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task1(mail);
        }
   }
   else if (params[0] == "task2"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task2(mail);
        }
   }
   else if (params[0] == "task3"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task3(mail);
        }
   }
   else if (params[0] == "task4"){
        if (params.count()!=2)
            return "Invalid data for task";
        else{
            return task4(mail);
        }
   }
   else{
             return "Invalid function name";
   }
   return "parse";
}

QByteArray rege(const QString& email, const QString& role, const QString& password,const QString& verifypass){
    if(password!=verifypass)                         
    {
        return "Passwords are not same";
    }
    QString query = QString("INSERT INTO users (mail, pass, role) VALUES(\"%1\", \"%2\", \"%3\")").arg(email, password ,role);
    
    Database::getInstance()->execQuery(query);  
    QString s = Database::getInstance()->execQuery("SELECT * from users where mail = \"" + email+"\"");
    if (s.size()>0) {
        return "rege+";
    } else {
        return "rege-";
    }
}

QByteArray auth(const QString& email,const QString& password){
    QString query = QString("SELECT * FROM users WHERE mail = \"" + email+"\"");
    qDebug()<<query;
    if (Database::getInstance()->execQuery(query).size()>0){  
        return "auth+";
        Database::getInstance()->execQuery("UPDATE users SET in_sys = 1 WHERE mail = \"" + email+"\"");
    }
    else                                                                  
        return "auth- ";
}

QString stat(const QString& email){
   QString query = ("SELECT task1, task2, task3, task4 FROM users WHERE mail = \"" + email+"\"");
   qDebug()<<query;
   QString response = "";
    if (Database::getInstance()->execQuery(query).size()>0){  
        response = Database::getInstance()->execQuery(query);
        return response;
    }
    else                                                               
        return "stat-";
}

QString task1(QStringList params, int descriptor){
    QString answer_stud = params[0]; 
    QString right_answer = ""; 
    QList <QString> Edges; 
    Edges.clear();
    Edges.push_back(params[1]);Edges.push_back(params[2]);Edges.push_back(params[1]);Edges.push_back(params[7]);Edges.push_back(params[1]);Edges.push_back(params[8]);
    Edges.push_back(params[2]);Edges.push_back(params[6]);Edges.push_back(params[3]);Edges.push_back(params[5]);Edges.push_back(params[4]);
    Edges.push_back(params[5]);Edges.push_back(params[5]);Edges.push_back(params[6]);Edges.push_back(params[5]);Edges.push_back(params[9]);
    QMap <QString,int> spisok; 
    spisok.clear();
    for (int i=1;i<10;i++){
        spisok[QString::number(i)]=0;
    }
    for (int i=0;i<Edges.size();i++){
        spisok[Edges[i]]++;
    }
    QString temp;
    for (int j=0;j<((Edges.size()/2)-1);j++){ 
        for (int k=1;k<10;k++){
            if (spisok[QString::number(k)]==1){
                temp = QString::number(k); 
                break;
            }
        }
        for (int i=0;i<8;i++){
            if (Edges[i*2]==temp){
                spisok[Edges[i*2]]--; spisok[Edges[i*2+1]]--; 
                right_answer += Edges[i*2+1];
                Edges[i*2] = "-1"; Edges[i*2+1] = "-1"; 
                break;
            }
            if (Edges[i*2+1]==temp){
                spisok[Edges[i*2]]--; spisok[Edges[i*2+1]]--;
                right_answer += Edges[i*2];
                Edges[i*2] = "-1"; Edges[i*2+1] = "-1"; 
                break;
            }
        }
    }
    QString right;
    if (answer_stud==right_answer){
        right = '+';
    }
    else{
        right = '-';
    }
    QString ans = DataBase::getInstance()->sendQuerry("SELECT task1 FROM users WHERE Socket_id = " + QString::number(descriptor),"task1",right,descriptor);
    if ( right =="+"){
        return "Correct answer";
    }
    else{
        return "Wrong answer, right answer: " + right_answer;
    }
}
QString task2(QStringList params, int descriptor){
    int answer_stud = params[0].toInt(); 
    int x_2 = params[1].toInt(); 
    int y_2 = params[2].toInt(); 
    int real_ans = 0; 
    
    QString right;
    if (answer_stud==real_ans){
        right = '+';
    }
    else{
        right = '-';
    }
    QString ans = DataBase::getInstance()->sendQuerry("SELECT task2 FROM users WHERE Socket_id = " + QString::number(descriptor),"task2",right,descriptor);
    if ( right =="+"){
        return "Correct answer";
    }
    else{
        return "Wrong answer";
    }
}
QString task3(QStringList params, int descriptor){
    int answer_stud = params[0].toInt(); 
    Graph g(6);
    g.addEdge(0, 1, params[1].toInt());
    g.addEdge(0, 2, params[2].toInt());
    g.addEdge(1, 2, params[3].toInt());
    g.addEdge(1, 3, params[4].toInt());
    g.addEdge(2, 1, params[5].toInt());
    g.addEdge(2, 4, params[6].toInt());
    g.addEdge(3, 2, params[7].toInt());
    g.addEdge(3, 5, params[8].toInt());
    g.addEdge(4, 3, params[9].toInt());
    g.addEdge(4, 5, params[10].toInt());
    int maxFlow = g.maxFlow(0, 5);
    QString right;
    if (answer_stud== maxFlow){
        right = '+';
    }
    else{
        right = '-';
    }
    QString ans = DataBase::getInstance()->sendQuerry("SELECT task3 FROM users WHERE Socket_id = " + QString::number(descriptor),"task3",right,descriptor);
    if ( right =="+"){
        return "Correct answer";
    }
    else{
        return "Wrong answer, right answer: " + QString::number(maxFlow);
    }
    return ans;
}
QString task4(QStringList params, int descriptor){
    int answer_stud = params[0].toInt(); 
    int x_4 = params[1].toInt(); 
    int y_4 = params[2].toInt(); 
    int real_ans = 0; 
    
    QString right;
    if (answer_stud==real_ans){
        right = '+';
    }
    else{
        right = '-';
    }
    QString ans = DataBase::getInstance()->sendQuerry("SELECT task4 FROM users WHERE Socket_id = " + QString::number(descriptor),"task4",right,descriptor);
    if ( right =="+"){
        return "Correct answer";
    }
    else{
        return "Wrong answer";
    }
}
