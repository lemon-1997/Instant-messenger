#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "mysql.h"

class clientwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit clientwindow(const QString * name,QWidget *parent = nullptr);
    QString user_name;
    QString cfd="00";
    QTcpSocket *tcpClient;
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent* event);

signals:
    void mainshow();

public slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

};

#endif // CLIENTWINDOW_H
