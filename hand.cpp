#include "hand.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QString>
#include <QTimer>

#include <inttypes.h>

#include "consts.h"

Hand::Hand()
{
	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mCurrentPosition.prepend(0);
	}

	setPortSettings();
}

Hand::~Hand()
{
	if (mPort->isOpen()) {
		stopSendingData();
	}

	delete mPort;
}

void Hand::connectHardwareHand()
{
}

void Hand::startSendingData()
{
	mPort->open(QIODevice::ReadWrite);

//	QTimer::singleShot(1000, this, SLOT(setStartValues()));

	QObject::connect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Hand::stopSendingData()
{
	QObject::disconnect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

	mPort->close();
}

bool Hand::isDataSending()
{
	return mPort->isOpen();
}

bool Hand::isPortSet()
{
	return !(mPort->portName().isEmpty());
}

void Hand::moveMotor(const int &num, const int &value)
{
	if (mPort->isOpen()) {
		QString sendData;

		sendData = separator
			+ QString::number(num)
			+ separator
			+ QString::number(value);

		mPort->write(sendData.toLocal8Bit());
	}
}

QList<int> *Hand::currentPosition()
{
	return &mCurrentPosition;
}

void Hand::setStartValues()
{
	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		moveMotor(i, HandConsts::startMotorValue);
	}
}

void Hand::onReadyRead()
{
	if (!mPort->bytesAvailable()) {
		return;
	}

	mBytes = mPort->readAll();

	if (!hasHeader()) {
		return;
	}

	getDataFromMotors();

	emit dataIsRead();
}

void Hand::setPortSettings()
{
	mPort = new QSerialPort;

	mPort->setPortName("ttyACM0");

	mPort->setBaudRate(QSerialPort::Baud9600);
	mPort->setDataBits(QSerialPort::Data8);
	mPort->setParity(QSerialPort::NoParity);
	mPort->setStopBits(QSerialPort::OneStop);
	mPort->setFlowControl(QSerialPort::NoFlowControl);
}

bool Hand::hasHeader()
{
	union {
		char chars[4];
		uint32_t header;
	} head;

	for (int i = 0; i < 4; i++) {
		head.chars[i] = mBytes[i];
	}

	return ((int)head.header == HandConsts::header);
}

void Hand::getDataFromMotors()
{
	union {
		char chars[HandConsts::numberOfMotors * 4];
		uint32_t vals[HandConsts::numberOfMotors];
	} motors;

	for (int i = 4; i < HandConsts::numberOfMotors * 4 + 4; i++) {
		motors.chars[i - 4] = mBytes[i];
	}

	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mCurrentPosition[i] = (int)motors.vals[i];
	}
}
