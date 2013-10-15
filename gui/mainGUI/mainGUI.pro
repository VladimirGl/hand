#-------------------------------------------------
#
# Project created by QtCreator 2013-10-15T22:41:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainGUI
TEMPLATE = app

include(../../include.pri)


SOURCES += main.cpp\
		mainwindow.cpp \
		../action/action.cpp \

HEADERS  += mainwindow.h \
		../action/action.h \


FORMS    += mainwindow.ui \
		../action/action.ui

