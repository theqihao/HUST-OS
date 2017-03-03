#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T15:36:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    head.cpp

HEADERS  += mainwindow.h \
    head.h

FORMS    += mainwindow.ui

DISTFILES += \
    image.jpg

RESOURCES += \
    qrc.qrc
