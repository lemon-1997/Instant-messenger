#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QCloseEvent>

class chatwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit chatwindow(const QString& name,QWidget *parent = nullptr);
    QString massage;
    QString user_name;
    void get_massage(QString& buf,QString& user);
    QTextEdit * rec_win;
    void closeEvent(QCloseEvent *event);

signals:
    void send_massage();
    void close_chat();


public slots:

};

#endif // CHATWINDOW_H
