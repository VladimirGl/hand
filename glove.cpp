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
	mIsConnectionMode = false;

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
	qDebug() << "try: " << portName;

	mIsConnectionMode = true;

	mPort->setPortName(portName);
	startSendingData();

	QTimer::singleShot(2000, this, SLOT(connectionTry()));
}

void Glove::startSendingData()
{
	if (!mPort->open(QIODevice::ReadWrite)) {
		return;
	}

	setPortSettings();

	QObject::connect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));\
}

void Glove::stopSendingData()
{
	QObject::disconnect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

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
	qDebug() << "tryread";

	if (!mPort->bytesAvailable()) {
		return;
	}

	mBytes = mPort->readAll();

	qDebug() << "rly";

	if (mBytes.size() < (headerBytes + sensorDataBytes * GloveConsts::numberOfSensors + tailBytes)) {
		return;
	}

	qDebug() << "not, rly?";

	if (!hasHeader()) {
		return;
	}

	qDebug() << "headerlol";

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
	qDebug() << "trynext: " << mIsGloveSet;

	mIsConnectionMode = false;

	if (mIsGloveSet) {
		stopSendingData();
		emit connectionTryEnd(true);

		return;
	}

	stopSendingData();
	emit connectionTryEnd(false);
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
		char chars[headerBytes];
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
