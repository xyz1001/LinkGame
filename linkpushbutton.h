#ifndef LINKPUSHBUTTON_H
#define LINKPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class LinkPushButton : public QPushButton
{
    Q_OBJECT
public:
    LinkPushButton(int id, int type, const QString & text, QWidget * parent = 0);
    void setX(int x);
    void setY(int y);

    int id;
    int type;
    bool isShown;
    int x;
    int y;

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

public slots:
    void transmitID();

signals:
    void btnID(int id);
};

#endif // LINKPUSHBUTTON_H
