#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysql.h"
#include "clientwindow.h"
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int window_x=400,window_y=300;
    ui->setupUi(this);
    this->setWindowTitle("飞讯");
    this->setFixedSize(window_x,window_y);

    connect(ui->pushButton_login,SIGNAL(clicked()),this,SLOT(logined()));
    connect(ui->pushButton_signup,SIGNAL(clicked()),this,SLOT(signup()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logined()
{
    QString name = ui->lineEdit_name->text();
    QString passwd = ui->lineEdit_password->text();
    QString sql = "select user_name, user_password from users where user_name = '" + name + "'and user_password ='" + passwd + "'";
    mysql db;

    clientwindow * client = new clientwindow(&name);
    connect(client,&clientwindow::mainshow,[=](){
        this->show();
        QMessageBox msgBox;
        msgBox.setWindowTitle("飞讯");
        msgBox.setText( "登陆失败, 网络没有联通");
        msgBox.exec();
    });

    if( db.queryDB(sql) )
    {  
        this->hide();
        client->show();
    }
    else
    {
        QMessageBox::information(this, "登陆失败", "用户名或密码错误");
    }


}

void MainWindow::signup()
{
    QString name = ui->lineEdit_name->text();
    QString passwd = ui->lineEdit_password->text();
    QString str_null = "";
    if(name==str_null||passwd==str_null){
        QMessageBox::information(this, "注册失败", "用户名或密码非空");
        return ;
    }
    if(name.length()>20||passwd.length()>20){
        QMessageBox::information(this, "注册失败", "用户名或密码过长");
        return ;
    }

    QString sql = "select user_name from users where user_name = '" + name +"';";
    mysql db;
    if( db.queryDB(sql) )
    {
        QMessageBox::information(this, "注册失败", "用户名重复");
    }
    else
    {
        sql = "insert into users (user_name, user_password) values ('" + name + "', '" + passwd + "');";
        db.queryDB(sql);
        QMessageBox::information(this, "注册成功", "现在可以登陆了");
    }

}
