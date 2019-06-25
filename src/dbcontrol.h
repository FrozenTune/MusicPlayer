#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include <QMutex>
#include <QMutexLocker>

class DBControl
{
public:
    DBControl();
    ~DBControl();

    QSqlDatabase db;

    bool connectDb();
    void disconnectDb();

    void initQueryModel(QSqlQueryModel *myModel,QSqlDatabase *db,const QString sqlQuery);    //初始化表格的model

    static DBControl* instance();       //单例模式设计:使用DBControl::instance()调用此对象

private:
    static DBControl *_pInstance;       //存放放置本类单例的指针
    static QMutex _mutex;               //存放本类的进程锁
};

#endif // CONNECTDB_H
