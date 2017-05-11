#include "mainwindow.h"
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMessageBox::information(0, tr("Game Goal"),
                             tr("Get more than 3000 scores!"));
    round = 1;
    scoreNumber = 0;
    previousScore = 0;
    setWindowTitle(tr("X Link Game - ROUND %1").arg(round));
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(UNIT_LENGTH * (SIZE + 2), UNIT_LENGTH * (SIZE + 2) + 2 * SPACE + OBJECT_HEIGHT);
    widget = new QWidget(this);
    widget->resize(UNIT_LENGTH * (SIZE + 2), UNIT_LENGTH * (SIZE + 2) + SPACE * 2 + OBJECT_HEIGHT);
    setCentralWidget(widget);
    widget->setStyleSheet(".QWidget{ border-image:url(:/background);}");

    scoreLabel = new QLabel(tr("Score: "), widget);
    scoreLabel->resize(OBJECT_WIDTH,OBJECT_HEIGHT);
    scoreLabel->move(SPACE, SPACE);

    score = new QLabel(widget);
    score->resize(OBJECT_WIDTH,OBJECT_HEIGHT);
    score->move(SPACE+OBJECT_WIDTH, SPACE);
    score->setText("0");

    timeLabel = new QLabel(tr("Time: "), widget);
    timeLabel->resize(OBJECT_WIDTH,OBJECT_HEIGHT);
    timeLabel->move(2 * SPACE + 2 * OBJECT_WIDTH, SPACE);

    totalTime = new QProgressBar(widget);
    totalTime->resize(4 * OBJECT_WIDTH, OBJECT_HEIGHT);
    totalTime->move(2 * SPACE + 3 * OBJECT_WIDTH, SPACE);
    totalTime->setRange(0,150);
    totalTime->setValue(150);

    startButton = new QPushButton(tr("Start"), widget);
    startButton->resize(2 * OBJECT_WIDTH,OBJECT_HEIGHT);
    startButton->move(UNIT_LENGTH * (SIZE + 2) - (2 * SPACE + 4 * OBJECT_WIDTH), SPACE);

    pauseButton = new QPushButton(tr("Pause"), widget);
    pauseButton->resize(2 * OBJECT_WIDTH,OBJECT_HEIGHT);
    pauseButton->move(UNIT_LENGTH * (SIZE + 2) - (SPACE + 2 * OBJECT_WIDTH), SPACE);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::slotStart);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::slotPause);
    pauseButton->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimerStart);
    setStyleSheet("QWidget{font:20px 楷体;"
                  "color:blue;}");

    isStarted = false;
    isPaused = false;
}

MainWindow::~MainWindow()
{

}

void MainWindow::setGame(int time)
{
    setWindowTitle(tr("X Link Game - ROUND %1").arg(round));
    linkgame = new LinkGame(widget);
    linkgame->move(0, 2 * SPACE + OBJECT_HEIGHT);
    linkgame->show();
    connect(linkgame, &LinkGame::remove, this, &MainWindow::slotGetScore);
    connect(linkgame, &LinkGame::win, this, &MainWindow::slotWin);
    isStarted = true;
    isPaused = false;
    totalTime->setMaximum(time);
    totalTime->setValue(time);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() & Qt::LeftButton) && isPressed)
    {
        move(e->globalPos() - relativePos);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        relativePos = e->globalPos() - pos();
        isPressed = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isPressed = false;
    }
}

void MainWindow::slotWin()
{
    timer->stop();
    scoreNumber += totalTime->value() * 10;
    score->setText(QString::number(scoreNumber));
    startButton->setText(tr("Start"));
    pauseButton->setEnabled(false);
    switch(QMessageBox::information(this, tr("Pass Round %1").arg(round), tr("Congratulations! Continue?"),
                             QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes))
    {
    case QMessageBox::Yes:
    {
        round += 1;
        totalTime->setValue(totalTime->maximum());
        previousScore = scoreNumber;
        delete linkgame;
        isStarted = false;
        break;
    }
    case QMessageBox::No:
    {
        QMessageBox::information(this, tr("Final Score"),
                                 tr("Your final score is %1, pass %2 round").arg(scoreNumber).arg(round));
        showCongratulations(scoreNumber);
        break;
    }
    default:
        break;
    }
}

void MainWindow::slotStart()
{
    if(!isStarted)
    {
        pauseButton->setEnabled(true);
        startButton->setText(tr("Restart"));
        setGame(175 - round * 25);
        timer->start(1 * 1000);
    }
    else
    {
        startButton->setText(tr("start"));
        isStarted = false;
        isPaused = false;
        pauseButton->setEnabled(false);
        pauseButton->setText(tr("Pause"));
        timer->stop();
        delete linkgame;
        scoreNumber = previousScore;
        score->setText(QString::number(scoreNumber));

        totalTime->setValue(totalTime->maximum());
    }
}

void MainWindow::slotPause()
{
    if(!isPaused)
    {
        isPaused = true;
        timer->stop();
        linkgame->hide();
        pauseButton->setText(tr("Continue"));
    }
    else
    {
        isPaused = false;
        timer->start(1 * 1000);
        linkgame->show();
        pauseButton->setText(tr("Pause"));
    }
}

void MainWindow::slotTimerStart()
{
    int remainedTime = totalTime->value() - 1;
    totalTime->setValue(remainedTime);
    if(remainedTime == 0)
    {
        delete linkgame;
        timer->stop();
        switch(QMessageBox::information(this, tr("Fail"), tr("Fail to pass this round! Continue?"),
                                 QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes))
        {
        case QMessageBox::Yes:
        {
            isStarted = false;
            isPaused = false;
            pauseButton->setEnabled(false);
            pauseButton->setText(tr("Pause"));
            scoreNumber = previousScore;
            score->setText(QString::number(scoreNumber));
            startButton->setText(tr("Start"));
            totalTime->setValue(totalTime->maximum());
            break;
        }
        case QMessageBox::No:
        {
            QMessageBox::information(this, tr("Final Score"),
                                     tr("Your final score is %1, pass %2 round").arg(scoreNumber).arg(round - 1));
            showCongratulations(scoreNumber);
            break;
        }
        default:
            break;
        }
    }
}

void MainWindow::slotGetScore()
{
    scoreNumber += 10;
    score->setText(QString::number(scoreNumber));
}

void MainWindow::showCongratulations(int score)
{
    startButton->setEnabled(false);
    pauseButton->setEnabled(false);
    this->score->setText(QString::number(score));
    if(score > 3000)
    {
        girlsDay = new Congratulations(this);
        girlsDay->move(10, 200);
        girlsDay->show();
        timer->start(10 * 1000);
        connect(timer, &QTimer::timeout, this, &MainWindow::close);
    }
    else
        close();
}
