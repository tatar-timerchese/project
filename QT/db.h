#ifndef DB_H
#define DB_H

#include <QCoreApplication>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

class DataBase;

class DataBaseDestroyer
{
private:
    DataBase *instance;
public:
    ~DataBaseDestroyer() { delete instance; }
    void initialize(DataBase *link){ instance = link; }
};

class DataBase
{
private:
    static DataBase *instance;
    static DataBaseDestroyer destroyer;
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
protected:
    DataBase()
    {
        DB.setDatabaseName("./TestDB.db");

        if(!DB.open())
            qDebug()<<DB.lastError().text();
    }
    DataBase(const DataBase &) = delete;
    DataBase &operator = (DataBase &) = delete;
    ~DataBase() { DB.close(); }
    friend class DataBaseDestroyer;
public:
    QString query_execute(QList<QString> query_list)
    {
        QSqlQuery query(DB);
        query.prepare(query_list[0]);
        query_list.pop_front();
        while(!query_list.isEmpty())
        {
            query.bindValue(query_list[0],query_list[1]);
            query_list.pop_front();
            query_list.pop_front();
        }

        query.exec();

        QString result;
        QSqlRecord record = query.record();
        int column_count = record.count();

        while (query.next())
        {
            for (int i = 0; i < column_count; ++i)
            {
                result.append(query.value(i).toString());
                if (i < column_count - 1)
                {
                    result.append(",");
                }
            }
            result.append(";");
        }
        return result;
    }

    static DataBase *Connect(){
        if (!instance)
        {
            instance = new DataBase();
            destroyer.initialize(instance);
        }
        return instance;
    }
};

DataBase *DataBase::instance;
DataBaseDestroyer DataBase::destroyer;

#endif // DB_H
