#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>
#include <QMouseEvent>
#include "linkgame.h"
#include "congratulations.h"

const int OBJECT_WIDTH = 50;
const int OBJECT_HEIGHT = 40;
const int SPACE = 10;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setGame(int time);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void slotWin();
    void slotStart();
    void slotPause();
    void slotTimerStart();
    void slotGetScore();
private:
    QWidget* widget;
    QLabel* scoreLabel;
    QLabel* score;
    QLabel* timeLabel;
    QProgressBar* totalTime;
    QPushButton* startButton;
    QPushButton* pauseButton;
    LinkGame* linkgame;
    Congratulations* girlsDay;

    QTimer* timer;
    int round;
    int scoreNumber;
    int previousScore;
    bool isStarted;
    bool isPaused;
    bool isPressed = false;
    QPoint relativePos;

    void showCongratulations(int score);
};

#endif // MAINWINDOW_H
