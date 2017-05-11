#include "linkpushbutton.h"

LinkPushButton::LinkPushButton(int id, int type, const QString &text, QWidget *parent)
    :QPushButton(text, parent)
{
    this->id = id;
    this->type = type;
    isShown = false;
}

void LinkPushButton::setX(int x)
{
    this->x = x;
}

void LinkPushButton::setY(int y)
{
    this->y = y;
}

void LinkPushButton::mouseMoveEvent(QMouseEvent *e)
{
    QPushButton::mouseMoveEvent(e);
    e->accept();
}

void LinkPushButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    e->accept();
}

void LinkPushButton::transmitID()
{
    emit btnID(id);
}
