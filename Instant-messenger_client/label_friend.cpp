#include "label_friend.h"
#include <QDebug>

label_friend::label_friend(const QString& name,QWidget *parent) : QLabel(parent)
{
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    setFont(font);

    QString text = "用户：" + name;
    qDebug()<<text;
    setText(text);
}

void label_friend::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit clicked();
}
