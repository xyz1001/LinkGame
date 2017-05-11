#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T09:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = LinkGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linkgame.cpp \
    linkpushbutton.cpp \
    congratulations.cpp

HEADERS  += mainwindow.h \
    linkgame.h \
    linkpushbutton.h \
    congratulations.h

RESOURCES += \
    res.qrc

TRANSLATIONS = LinkGame_zh_CN.ts

RC_ICONS = icon.ico
