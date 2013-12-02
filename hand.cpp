#include "hand.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QString>
#include <QTimer>

#include <inttypes.h>

#include "consts.h"

#include <QDebug>

const int startByte = 0;

const int headerBytes = 4;
const int tailBytes = 4;
const int motorDataBytes = 4;

const int tailStartByte = headerBytes + motorDataBytes * HandConsts::numberOfMotors;
const int finishByte = tailStartByte + tailBytes;

Hand::Hand()
{
	mIsHandSet = false;
	mIsStartSendingData = false;
	mIsConnectionMode = false;

	mPortAvailableTimer = new QTimer(this);

	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mCurrentPosition.prepend(0);
	}

	mPort = new QSerialPort;
}

Hand::~Hand()
{
	if (mPort->isOpen()) {
		stopSendingData();
	}

	delete mPort;
}

void Hand::connectHardwareHand(const QString &portName)
{
	stopSendingData();

	mIsHandSet = false;
	mIsConnectionMode = true;

	mPort->setPortName(portName);
	startSendingData();

	QTimer::singleShot(2000, this, SLOT(connectionTry()));
}

bool Hand::startSendingData()
{
	if (!mPort->open(QIODevice::ReadWrite)) {
		return false;
	}

	setPortSettings();

	mIsStartSendingData = true;

	QObject::connect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

	return true;
}

void Hand::stopSendingData()
{
	QObject::disconnect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	QObject::disconnect(mPortAvailableTimer, SIGNAL(timeout()), this, SLOT(checkIsCanBeConnected()));

	mIsStartSendingData = false;

	mPort->close();
}

bool Hand::isDataSending() const
{
	return mPort->isOpen();
}

bool Hand::isPortSet() const
{
	return mIsHandSet;
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

QList<int> Hand::currentPosition() const
{
	return mCurrentPosition;
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

	if (mBytes.size() < (headerBytes + motorDataBytes * HandConsts::numberOfMotors + tailBytes)) {
		return;
	}

	if (!hasHeader()) {
		return;
	}

	getDataFromMotors();

	if (!hasTail()) {
		return;
	}

	if (!mIsHandSet) {
		mIsHandSet = true;
	}

	if (!mIsConnectionMode) {
		emit dataIsRead();
	}
}

void Hand::connectionTry()
{
	mIsConnectionMode = false;

	if (mIsHandSet) {
		stopSendingData();

		QObject::connect(mPortAvailableTimer, SIGNAL(timeout()), this, SLOT(checkIsCanBeConnected()));
		mPortAvailableTimer->start(4000);

		emit connectionTryEnd(true);

		return;
	}

	stopSendingData();
	emit connectionTryEnd(false);
}

void Hand::checkIsCanBeConnected()
{
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

	bool isPortAvailable = false;

	for (int i = 0; i < list.size(); i++) {
		if (list.at(i).portName() == mPort->portName()) {
			isPortAvailable = true;
		}
	}

	if (!isPortAvailable) {
		if (mIsStartSendingData) {
			stopSendingData();
		}

		mIsHandSet = false;
	}
}

bool Hand::hasHeader() const
{
	union {
		char chars[headerBytes];
		uint32_t value;
	} head;

	for (int i = startByte; i < headerBytes; i++) {
		head.chars[i] = mBytes[i];
	}

	return ((int)head.value == HandConsts::header);
}

bool Hand::hasTail() const
{
	union {
		char chars[tailBytes];
		uint32_t value;
	} tail;

	for (int i = tailStartByte; i < finishByte; i++) {
		tail.chars[i - tailStartByte] = mBytes[i];
	}

	return ((int)tail.value == HandConsts::tail);
}

void Hand::getDataFromMotors()
{
	union {
		char chars[HandConsts::numberOfMotors * motorDataBytes];
		uint32_t vals[HandConsts::numberOfMotors];
	} motors;

	for (int i = headerBytes; i < HandConsts::numberOfMotors * motorDataBytes + headerBytes; i++) {
		motors.chars[i - headerBytes] = mBytes[i];
	}

	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mCurrentPosition[i] = (int)motors.vals[i];
	}
}

void Hand::setPortSettings()
{
	mPort->setBaudRate(QSerialPort::Baud115200);
	mPort->setDataBits(QSerialPort::Data8);
	mPort->setParity(QSerialPort::NoParity);
	mPort->setStopBits(QSerialPort::OneStop);
	mPort->setFlowControl(QSerialPort::NoFlowControl);
}
