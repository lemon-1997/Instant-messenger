#include "clientwindow.h"
#include "label_friend.h"
#include "chatwindow.h"
#include <stdio.h>
#include <QPainter>
#include <QDebug>
#include <QTimer>

clientwindow::clientwindow(const QString * name,QWidget *parent) : QMainWindow(parent)
{
    int window_x=200,window_y=600;
    this->setWindowTitle("飞讯");
    this->setFixedSize(window_x,window_y);
    user_name = *name;

    label_friend * user = new label_friend(user_name);
    user->setParent(this);
    user->setFixedSize(200,50);
    user->move(0,0);
    connect(user,&label_friend::clicked,[=](){
        qDebug()<<"你正在与"<<user->user_name<<"联通";
    });

    QString sql = "select * from friends where user_name = '" + user_name +"';";
    QSqlQuery query;
    query.exec(sql);
    if(query.next())
    {
        for(int i=1;i<=10;++i){
            if(query.value(i).toString()=="")
                continue;
            label_friend * friends = new label_friend(query.value(i).toString());
            friends->setParent(this);
            friends->setFixedSize(200,50);
            friends->move(0,i*50);
            chatwindow * chat = new chatwindow(friends->user_name);
            connect(this,&clientwindow::recv_massage,[=](){
                chat->get_massage(buf,send_user);
            });
            connect(chat,&chatwindow::send_massage,[=](){
               // qDebug()<<chat->massage;
                QString data = chat->massage;
                QString sql_fd = "select user_cfd from users where user_name = '" + chat->user_name +"';";
                QSqlQuery query;
                query.exec(sql_fd);
                if(query.next())
                {
                    data += query.value(0).toString();
                   // qDebug()<<sfd;
                }
                sql_fd = "select user_cfd from users where user_name = '" + user_name +"';";
                query.exec(sql_fd);
                if(query.next())
                {
                    data += query.value(0).toString();
                    tcpClient->write(data.toLatin1());
                }
            });
            connect(friends,&label_friend::clicked,[=](){
                qDebug()<<"你正在与"<<friends->user_name<<"联通";
                chat->show();
            });
        }
    }

    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(ReadError(QAbstractSocket::SocketError)));

    tcpClient->connectToHost("10.199.159.156", 9999);
    if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("飞讯");
        msgBox.setText( "登陆成功, 欢迎使用飞讯");
        msgBox.exec();
    }
    else {
        QTimer::singleShot(500,this,[=](){
            this->close();
            emit mainshow();
        });
    }

}


void clientwindow::closeEvent(QCloseEvent* event)
{
    cfd="00";
    qDebug()<<"看这里";
    QString sql = "update users set user_cfd = '" + cfd +"' where user_name = '"+user_name+"';";
    mysql db;
    db.queryDB(sql);
}

void clientwindow::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    if(!buffer.isEmpty())
    {
       // ui->edtRecv->append(buffer);
       QString sql,sfd;
       if(cfd=="00"){
            cfd = buffer;
            if(cfd.length()==1){
                cfd = "0" + cfd;
            }
            qDebug()<<cfd;
            sql = "update users set user_cfd = '" + cfd +"' where user_name = '"+user_name+"';";
            mysql db;
            db.queryDB(sql);
        }
        else{
           buf = buffer;
           sfd = buf.mid(buf.length()-2);
           buf = buf.mid(0,buf.length()-4);
           qDebug()<<"sfd="<<sfd;
           sql = "select user_name from users where user_cfd = '" + sfd +"';";
           QSqlQuery query;
           query.exec(sql);
           if(query.next())
           {
               send_user = query.value(0).toString();
               qDebug()<<"来自"<<send_user;
           }
           emit recv_massage();
        }
    }
}

void clientwindow::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    msgBox.exec();
}

void clientwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawLine(0,50,200,50);

    QString sql = "select * from friends where user_name = '" + user_name +"';";
    QSqlQuery query;
    query.exec(sql);
    if(query.next())
    {
        int j = 2;
        for(int i=1;i<=10;++i){
            if(query.value(i).toString()=="")
                continue;
            painter.drawLine(0,j*50,200,j*50);
            j++;
            qDebug() << query.value(i).toString();
        }
    }
 //   for(int i=0;i<10;++i){
//
  //  }
}
