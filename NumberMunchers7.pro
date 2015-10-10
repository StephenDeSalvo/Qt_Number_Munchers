#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T21:31:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumberMunchers7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h \
    Documentation.h

FORMS    += mainwindow.ui \
    gameboard.ui

RESOURCES += \
    Images.qrc
