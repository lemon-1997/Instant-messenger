#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include "mysql.h"

mysql::mysql(QObject *parent) : QObject(parent)
{
    dbDriver="QMYSQL";
    dbName="info";
    userName="root";
    userPwd="123456";
    hostName="localhost";
   // hostPort=5432;
    connDB();
}

bool mysql::connDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(dbDriver);//添加驱动
    db.setHostName(hostName); //设置主机名
    db.setDatabaseName(dbName); //设置数据库名
    db.setUserName(userName); //设置用户名
    db.setPassword(userPwd); //设置用户密码

    //发送连接
    if(!db.open())
    {
    //	qDebug() << QSqlDatabase::drivers();
        qDebug() << db.lastError();
        return false;
    }
    return true;
}

bool mysql::queryDB(const QString &sql)
{
    QSqlQuery query;
    query.exec(sql);

    if(query.next())
    {
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
        return true;
    }
    return false;
}


