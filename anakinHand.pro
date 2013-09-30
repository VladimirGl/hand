#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:42:58
#
#-------------------------------------------------

QT       += serialport \
	core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = anakinHand
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp \
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
	actionPerfomer.cpp \
    kalmanFilter.cpp \
    userFileSaver.cpp

HEADERS  += mainWindow.h \
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
	actionPerfomer.h \
    kalmanFilter.h \
    userFileStructure.h \
    userFileSaver.h

FORMS    += mainWindow.ui
