#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:42:58
#
#-------------------------------------------------

QT       += serialport \
	core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(gui/gui.pri)

TARGET = anakinHand
TEMPLATE = app

SOURCES += main.cpp\
	actionSaver.cpp \
	actionLoader.cpp \
	glove.cpp \
    hand.cpp \
    gloveInterface.cpp \
    user.cpp \
    action.cpp \
    calibrator.cpp \
    translator.cpp \
    handInterface.cpp \
    kalmanFilter.cpp \
    userFileSaver.cpp \
    userFileLoader.cpp \
    fileActionPerformer.cpp

HEADERS  += \
	actionSaver.h \
	actionFileStructure.h \
	actionLoader.h \
    glove.h \
    hand.h \
    gloveInterface.h \
    user.h \
    action.h \
    calibrator.h \
    translator.h \
    handInterface.h \
    consts.h \
    degreeOfFreedom.h \
    kalmanFilter.h \
    userFileStructure.h \
    userFileSaver.h \
    userFileLoader.h \
    fileActionPerformer.h

FORMS    +=

SUBDIRS +=
