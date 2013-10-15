#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T16:24:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

INCLUDEPATH += C:/Qt/qwt-6.1.0/qwt-6.1.0/src
LIBS += -LC:/Qt/qwt-6.1.0/qwt-6.1.0/lib -lqwtd


SOURCES += main.cpp\
        mainWindow.cpp \
    plotWidget.cpp \
    graphicalWidget.cpp

HEADERS  += mainWindow.h \
    plotWidget.h \
    graphicalWidget.h

FORMS    += mainWindow.ui
