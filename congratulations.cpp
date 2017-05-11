#include "congratulations.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

Congratulations::Congratulations(QWidget *parent) : QWidget(parent)
{
    QPixmap pix;
    pix.load(":/congratulations");
    resize(pix.size());
    setMask(pix.mask());
}

void Congratulations::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/congratulations"));
}
