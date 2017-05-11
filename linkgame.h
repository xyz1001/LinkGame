#ifndef LINKGAME_H
#define LINKGAME_H

#include <QWidget>
#include "linkpushbutton.h"
#include <QPainter>
#include <QPen>
#include <QTimer>

const int SIZE = 8;
const int UNIT_LENGTH = 60;

class LinkGame : public QWidget
{
    Q_OBJECT
public:
    explicit LinkGame(QWidget *parent = 0);

    bool isEliminable(int m, int n);
    bool verticalLink(QPoint a, QPoint b) const;
    bool HorizontalLink(QPoint a, QPoint b) const;
    bool crossOne(QPoint a, QPoint b) const;
    bool crossTwo(QPoint a, QPoint b) const;

private:
    int isChecked;
    LinkPushButton *linkBtn[SIZE * SIZE];
    bool hasBtn[SIZE + 2][SIZE + 2];
    int remained;
signals:
    void win();
    void remove();
public slots:
    void link(int i);
};

#endif // LINKGAME_H
