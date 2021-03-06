#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T16:42:58
#
#-------------------------------------------------

QT += serialport \
	core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(gui/gui.pri)
DEFINES += PRO_FILE_PWD=$$sprintf("\"\\\"%1\\\"\"", $$_PRO_FILE_PWD_)

TARGET = anakinHand
TEMPLATE = app


win32 {
    INCLUDEPATH += C:/Qt/qwt-6.1.0/qwt-6.1.0/src
    LIBS += -LC:/Qt/qwt-6.1.0/qwt-6.1.0/lib -lqwtd
} else {
}


SOURCES += main.cpp\
	actionSaver.cpp \
	actionLoader.cpp \
	glove.cpp \
	hand.cpp \
	gloveInterface.cpp \
	user.cpp \
	action.cpp \
	translator.cpp \
	handInterface.cpp \
	kalmanFilter.cpp \
	userFileSaver.cpp \
	userFileLoader.cpp \
	fileActionPerformer.cpp \
	gloveCalibrator.cpp \
	flexSensorCalibrator.cpp \
    fileUserPerfofmer.cpp

HEADERS += \
	actionSaver.h \
	actionFileStructure.h \
	actionLoader.h \
	glove.h \
	hand.h \
	gloveInterface.h \
	user.h \
	action.h \
	translator.h \
	handInterface.h \
	consts.h \
	degreeOfFreedom.h \
	kalmanFilter.h \
	userFileStructure.h \
	userFileSaver.h \
	userFileLoader.h \
	fileActionPerformer.h \
	gloveCalibrator.h \
	flexSensorCalibrator.h \
    fileUserPerfofmer.h \
    map.h
