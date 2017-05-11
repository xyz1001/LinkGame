#ifndef CONGRATULATIONS_H
#define CONGRATULATIONS_H

#include <QWidget>

class Congratulations : public QWidget
{
    Q_OBJECT
public:
    explicit Congratulations(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:
};

#endif // HAPPYGIRLSDAY_H
