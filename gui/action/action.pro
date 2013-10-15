#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T22:46:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = action
TEMPLATE = app


SOURCES += main.cpp \
		action.cpp \
		../../actionLoader.cpp \
		../../actionSaver.cpp \
		../../fileActionPerformer.cpp

HEADERS  += action.h \
		../../actionLoader.h \
		../../actionSaver.h \
		../../fileActionPerformer.h \
		../../actionFileStructure.h

FORMS    += action.ui
