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
    bool connectDb();
    void disconnectDb();

    static DBControl* instance();       //单例模式设计:使用DBControl::instance()调用此对象

private:
    QSqlDatabase db;
    static DBControl *_pInstance;       //存放放置本类单例的指针
    static QMutex _mutex;               //存放本类的进程锁
};

#endif // CONNECTDB_H
