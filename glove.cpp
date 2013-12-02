#include "glove.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QTimer>
#include <QString>

#include <inttypes.h>

#include <QDebug>

#include "consts.h"

const int startByte = 0;

const int headerBytes = 4;
const int tailBytes = 4;
const int sensorDataBytes = 4;

const int tailStartByte = headerBytes + sensorDataBytes * GloveConsts::numberOfSensors;
const int finishByte = tailStartByte + tailBytes;

Glove::Glove()
{
	mIsGloveSet = false;
	mIsStartSendingData = false;
	mIsConnectionMode = false;

	mPortAvailableTimer = new QTimer(this);

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mLastData.prepend(0);
	}

	mPort = new QSerialPort;
}

Glove::~Glove()
{
	if (mPort->isOpen()) {
		stopSendingData();
	}

	delete mPort;
}

void Glove::connectHardwareGlove(const QString &portName)
{
	stopSendingData();

	mIsGloveSet = false;
	mIsConnectionMode = true;

	mPort->setPortName(portName);
	startSendingData();

	QTimer::singleShot(2000, this, SLOT(connectionTry()));
}

bool Glove::startSendingData()
{
	if (!mPort->open(QIODevice::ReadWrite)) {
		return false;
	}

	setPortSettings();

	mIsStartSendingData = true;

	QObject::connect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

	return true;
}

void Glove::stopSendingData()
{
	QObject::disconnect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	QObject::disconnect(mPortAvailableTimer, SIGNAL(timeout()), this, SLOT(checkIsCanBeConnected()));

	mIsStartSendingData = false;

	mPort->close();
}

bool Glove::isDataSending() const
{
	return mPort->isOpen();
}

bool Glove::isPortSet() const
{
	return mIsGloveSet;
}

QList<int> Glove::data() const
{
	return mLastData;
}

void Glove::onReadyRead()
{
	if (!mPort->bytesAvailable()) {
		return;
	}

	mBytes = mPort->readAll();

	if (mBytes.size() < (headerBytes + sensorDataBytes * GloveConsts::numberOfSensors + tailBytes)) {
		return;
	}

	if (!hasHeader()) {
		return;
	}

	getDataFromFlexSensors();

	if (!hasTail()) {
		return;
	}

	if (!mIsGloveSet) {
		mIsGloveSet = true;
	}

	if (!mIsConnectionMode) {
		emit dataIsRead();
	}
}

void Glove::connectionTry()
{
	qDebug() << "trynextGlove: " << mIsGloveSet;

	mIsConnectionMode = false;

	if (mIsGloveSet) {
		stopSendingData();

		QObject::connect(mPortAvailableTimer, SIGNAL(timeout()), this, SLOT(checkIsCanBeConnected()));
		mPortAvailableTimer->start(4000);

		emit connectionTryEnd(true);

		return;
	}

	stopSendingData();
	emit connectionTryEnd(false);
}

void Glove::checkIsCanBeConnected()
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

		mIsGloveSet = false;
	}
}

bool Glove::hasHeader() const
{
	union {
		char chars[headerBytes];
		uint32_t value;
	} head;

	for (int i = startByte; i < headerBytes; i++) {
		head.chars[i] = mBytes[i];
	}

	return ((int)head.value == GloveConsts::header);
}

bool Glove::hasTail() const
{
	union {
		char chars[tailBytes];
		uint32_t value;
	} tail;

	for (int i = tailStartByte; i < finishByte; i++) {
		tail.chars[i - tailStartByte] = mBytes[i];
	}

	return ((int)tail.value == GloveConsts::tail);
}

void Glove::getDataFromFlexSensors()
{
	union {
		char chars[GloveConsts::numberOfSensors * sensorDataBytes];
		uint32_t vals[GloveConsts::numberOfSensors];
	} fingers;

	for (int i = headerBytes; i < GloveConsts::numberOfSensors * sensorDataBytes + headerBytes; i++) {
		fingers.chars[i - headerBytes] = mBytes[i];
	}

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mLastData[i] = (int)fingers.vals[i];
	}
}

void Glove::setPortSettings()
{
	mPort->setBaudRate(QSerialPort::Baud115200);
	mPort->setDataBits(QSerialPort::Data8);
	mPort->setParity(QSerialPort::NoParity);
	mPort->setStopBits(QSerialPort::OneStop);
	mPort->setFlowControl(QSerialPort::NoFlowControl);
}
