#include "clientwindow.h"
#include "label_friend.h"
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

    connect(user,&label_friend::clicked,[=](){
        qDebug()<<"你正在与"<<user->user_name<<"联通";
    });
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
       if(cfd=="00"){
            cfd = buffer;
            if(cfd.length()==1){
                cfd = "0" + cfd;
            }
            qDebug()<<cfd;
            QString sql = "update users set user_cfd = '" + cfd +"' where user_name = '"+user_name+"';";
            mysql db;
            db.queryDB(sql);
        }
        else{

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
 //   for(int i=0;i<10;++i){
//
  //  }
}
