#ifndef LABEL_FRIEND_H
#define LABEL_FRIEND_H

#include <QLabel>
#include <QMouseEvent>

class label_friend : public QLabel
{
    Q_OBJECT
public:
    explicit label_friend(const QString& name,QWidget *parent = nullptr);
    QString user_name;

signals:
    void clicked();

public slots:

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
};

#endif // LABEL_FRIEND_H
