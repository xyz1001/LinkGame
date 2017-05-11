#include "linkgame.h"
#include <ctime>
#include <QList>

LinkGame::LinkGame(QWidget *parent) : QWidget(parent)
{
    srand(time(0));
    resize(UNIT_LENGTH * (SIZE + 2), UNIT_LENGTH * (SIZE + 2));
    isChecked = -1;
    for(int i = 0; i<SIZE * SIZE; ++i)
    {
        linkBtn[i] = new LinkPushButton(i, i/4, "", this);
        linkBtn[i]->resize(UNIT_LENGTH, UNIT_LENGTH);
        linkBtn[i]->setStyleSheet("border-image:url(:/" + QString::number(linkBtn[i]->type + 1) + ")");
        connect(linkBtn[i], &LinkPushButton::clicked, linkBtn[i], &LinkPushButton::transmitID);
        connect(linkBtn[i], &LinkPushButton::btnID, this, &LinkGame::link);
    }

    for(int i = 0; i<SIZE + 2; ++i)
        for(int j = 0; j<SIZE + 2; ++j)
        {
            hasBtn[i][j] = false;
        }

    int temp;
    for(int i = 1; i<SIZE + 1; ++i)
        for(int j = 1; j<SIZE + 1; ++j)
        {
            temp = rand() % (SIZE * SIZE);
            while(linkBtn[temp]->isShown)
                temp = (temp + 1) % (SIZE * SIZE);
            linkBtn[temp]->move(i * UNIT_LENGTH, j * UNIT_LENGTH);
            linkBtn[temp]->setX(i);
            linkBtn[temp]->setY(j);
            linkBtn[temp]->isShown = true;
            hasBtn[i][j] = true;
        }
    remained = SIZE * SIZE / 2;
}

bool LinkGame::verticalLink(QPoint a, QPoint b) const
{
    int yStart, yEnd;
    if(a.y() > b.y())
    {
        yStart = b.y(), yEnd = a.y();
    }
    else
    {
        yStart = a.y(), yEnd = b.y();
    }
    for(int i=yStart + 1; i<yEnd; ++i)
        if(hasBtn[a.x()][i])
            return false;
    return true;
}

bool LinkGame::HorizontalLink(QPoint a, QPoint b) const
{
    int xStart, xEnd;
    if(a.x() > b.x())
    {
        xStart = b.x(), xEnd = a.x();
    }
    else
    {
        xStart = a.x(), xEnd = b.x();
    }
    for(int i=xStart + 1; i<xEnd; ++i)
        if(hasBtn[i][a.y()])
            return false;
    return true;
}

bool LinkGame::crossOne(QPoint a, QPoint b) const
{
    QPoint m(a.x(), b.y()), n(b.x(), a.y());
    if((!hasBtn[a.x()][b.y()]) && HorizontalLink(b, m) && verticalLink(m, a))
        return true;
    if((!hasBtn[b.x()][a.y()]) && HorizontalLink(a, n) && verticalLink(n, b))
        return true;
    return false;

}

bool LinkGame::crossTwo(QPoint a, QPoint b) const
{
    int x = a.x();
    int y = a.y();
    while((--x) != -1 && !hasBtn[x][y])
    {
        if(crossOne(QPoint(x, y), b))
            return true;
    }

    x = a.x();
    y = a.y();
    while((++x) != SIZE + 2 && !hasBtn[x][y])
    {
        if(crossOne(QPoint(x, y), b))
            return true;
    }

    x = a.x();
    y = a.y();
    while((--y) != -1 && !hasBtn[x][y])
    {
        if(crossOne(QPoint(x, y), b))
            return true;
    }

    x = a.x();
    y = a.y();
    while((++y) != SIZE + 2 && !hasBtn[x][y])
    {
        if(crossOne(QPoint(x, y), b))
            return true;
    }
    return false;
}


bool LinkGame::isEliminable(int m, int n)
{
    QPoint a(linkBtn[m]->x, linkBtn[m]->y);
    QPoint b(linkBtn[n]->x, linkBtn[n]->y);
    if(a.x() == b.x() && verticalLink(a, b))
    {
        return true;
    }
    else if(a.y() == b.y() && HorizontalLink(a, b))
    {
        return true;
    }
    else if(crossOne(a, b))
    {
        return true;
    }
    else if(crossTwo(a, b))
    {
        return true;
    }
    else
        return false;
}

void LinkGame::link(int i)
{
    if(isChecked == -1)
    {
        isChecked = i;
        linkBtn[i]->setStyleSheet("border-image:url(:/"
                                  + QString::number(linkBtn[i]->type + 1) + ");border-radius:20px");
    }
    else if(isChecked == i)
    {
        isChecked = -1;
        linkBtn[i]->setStyleSheet("border-image:url(:/"
                                          + QString::number(linkBtn[i]->type + 1) + ")");
    }
    else
    {
        if(linkBtn[isChecked]->type == linkBtn[i]->type)
        {
            if(isEliminable(isChecked, i))
            {
                linkBtn[isChecked]->hide();
                linkBtn[i]->hide();
                hasBtn[linkBtn[isChecked]->x][linkBtn[isChecked]->y] = false;
                hasBtn[linkBtn[i]->x][linkBtn[i]->y] = false;
                isChecked = -1;
                remained--;
                emit remove();
                if(remained == 0)
                {
                    emit win();
                }
            }
            else
            {
                linkBtn[isChecked]->setStyleSheet("border-image:url(:/"
                                                  + QString::number(linkBtn[isChecked]->type + 1) + ")");
                isChecked = i;
                linkBtn[i]->setStyleSheet("border-image:url(:/"
                                          + QString::number(linkBtn[i]->type + 1) + ");border-radius:20px");
            }
        }
        else
        {
            linkBtn[isChecked]->setStyleSheet("border-image:url(:/"
                                              + QString::number(linkBtn[isChecked]->type + 1) + ")");
            isChecked = i;
            linkBtn[i]->setStyleSheet("border-image:url(:/"
                                      + QString::number(linkBtn[i]->type + 1) + ");border-radius:20px");
        }
    }
}

