#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class chatwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit chatwindow(const QString& name,QWidget *parent = nullptr);
    QString massage;
    QString user_name;
    void get_massage(QString& buf,QString& user);
    QTextEdit * rec_win;

signals:
    void send_massage();


public slots:

};

#endif // CHATWINDOW_H
