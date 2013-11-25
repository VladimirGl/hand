#include "glove.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QTimer>
#include <QString>

#include <inttypes.h>

#include "consts.h"

const int headerBytes = 4;
const int numberOfSensorsBytes = 4;
const int sensorDataBytes = 4;

const int workBytes = headerBytes + numberOfSensorsBytes;

Glove::Glove()
{
	mIsGloveSet = false;
	mIsConnectionMode = false;
	mNumberOfSensors = 1;

	for (int i = 0; i < mNumberOfSensors; i++) {
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
	mIsConnectionMode = true;

	mPort->setPortName(portName);
	startSendingData();

	QTimer::singleShot(1000, this, SLOT(connectionTry()));
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
	if (!mPort->bytesAvailable()) {
		return;
	}

	mBytes = mPort->readAll();

	if (mIsGloveSet) {
		if (mBytes.size() < (workBytes + sensorDataBytes * mNumberOfSensors)) {
			return;
		}
	}

	if (!hasHeader()) {
		return;
	}

	if (!hasNumberOfSensors()) {
		return;
	}

	getDataFromFlexSensors();

	if (!mIsGloveSet) {
		mIsGloveSet = true;
	}

	if (!mIsConnectionMode) {
		emit dataIsRead();
	}
}

void Glove::connectionTry()
{
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
		uint32_t header;
	} head;

	for (int i = 0; i < headerBytes; i++) {
		head.chars[i] = mBytes[i];
	}

	return ((int)head.header == GloveConsts::header);
}

bool Glove::hasNumberOfSensors()
{
	union {
		char chars[numberOfSensorsBytes];
		uint32_t number;
	} sensors;

	for (int i = headerBytes; i < workBytes; i++) {
		sensors.chars[i - headerBytes] = mBytes[i];
	}

	if (sensors.number >= 0) {
		if (!mIsGloveSet) {
			mNumberOfSensors = (int)sensors.number;
		}

		return true;
	}

	return false;
}

void Glove::getDataFromFlexSensors()
{
	union {
		char chars[GloveConsts::numberOfSensors * sensorDataBytes];
		uint32_t vals[GloveConsts::numberOfSensors];
	} fingers;

	for (int i = workBytes; i < mNumberOfSensors * sensorDataBytes + workBytes; i++) {
		fingers.chars[i - workBytes] = mBytes[i];
	}

	for (int i = 0; i < mNumberOfSensors; i++) {
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
