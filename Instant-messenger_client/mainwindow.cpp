#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mysql.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int window_x=400,window_y=300;
    ui->setupUi(this);
    this->setWindowTitle("飞讯");
    this->setFixedSize(window_x,window_y);

    connect(ui->pushButton_login,SIGNAL(clicked()),this,SLOT(logined()));





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
        if( db.queryDB(sql) )
        {
            qDebug()<<"login sucess";
        }
        else
        {

            qDebug()<<"login lose";
        }

}

