#include "chatwindow.h"
#include <QPushButton>
#include <QDebug>

chatwindow::chatwindow(const QString& name,QWidget *parent) : QMainWindow(parent)
{
    user_name = name;
    QString text = "用户：" + name;
    int window_x=800,window_y=600;
    this->setWindowTitle(text);
    this->setFixedSize(window_x,window_y);

    QTextEdit * recv_text = new QTextEdit();
    recv_text->setEnabled(false);
    recv_text->setParent(this);
    recv_text->setFixedSize(800,400);
    rec_win = recv_text;

    QTextEdit * send_text = new QTextEdit();
    send_text->setParent(this);
    send_text->setFixedSize(800,200);
    send_text->move(0,400);

    QPushButton * send_btn = new QPushButton();
    send_btn->setParent(this);
    send_btn->setFixedSize(100,50);
    send_btn->move(700,550);
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(20);
    send_btn->setFont(font);
    send_btn->setText("发送");

    connect(send_btn,&QPushButton::clicked,[=](){
         massage = send_text->toPlainText();
    //     qDebug()<<massage;
         emit send_massage();
    });
}

void chatwindow::get_massage(QString& buf,QString& user)
{
    qDebug()<<buf;
    if(user == user_name){
        rec_win->setText(buf);
    }
}

