#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

class clientwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit clientwindow(const QString * name,QWidget *parent = nullptr);
    ~clientwindow();
    QString user_name;
    QString cfd="00";
    QTcpSocket *tcpClient;
    void paintEvent(QPaintEvent *);

signals:
    void mainshow();

public slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

};

#endif // CLIENTWINDOW_H
