#include "dbcontrol.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QtWidgets/QApplication>
#include <QDebug>

#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

DBControl *DBControl::_pInstance = nullptr;     //初始化静态全局变量为空指针(默认值)
QMutex DBControl::_mutex;                       //在这个类中定义mutex

DBControl::DBControl()
{
}

DBControl::~DBControl()
{
    disconnectDb();
}

DBControl* DBControl::instance()    //单例调用入口
{
    if (!_pInstance)    //若当前没有过实例过DBControl类,其静态存放DBControl类的指针默认为空(nullptr),则将其实例化
    {
        QMutexLocker lock(&_mutex);
        //首次实例,将DBControl类静态存放的线程锁锁上
        //[其中调用了QMutexLocker,该类会根据mutex定义所在的作用域进行上锁;当作用域过去后会解锁]
        if (!_pInstance)
        {
            DBControl *pInstance = new DBControl(); //申请DBControl的实例(内存空间->构造DBControl)
            _pInstance = pInstance; //返回此实例指针
        }
    }
    return _pInstance;
}

bool DBControl::connectDb()
{
    bool ok=false;
    QSqlError err;

    db=QSqlDatabase::addDatabase("QSQLITE");    //数据库类型
    db.setDatabaseName(QApplication::applicationDirPath() + "/MusicPlayer.db"); //数据库地址
    DEBUG(QApplication::applicationDirPath() + "/MusicPlayer.db");
    DEBUG(db.isOpen());
    if (!db.open())     //尝试打开
    {
        err = db.lastError();
    }
    else ok=true;
    DEBUG(db.isOpen());

    return ok;
}

void DBControl::disconnectDb()
{
    if (db.isOpen()) db.close();
}
