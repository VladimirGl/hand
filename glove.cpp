#include "glove.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QString>

#include <inttypes.h>

#include "consts.h"

Glove::Glove()
{
	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mLastData.prepend(0);
	}

	setPortSettings();
}

Glove::~Glove()
{
	if (mPort->isOpen()) {
		stopSendingData();
	}

	delete mPort;
}

void Glove::connectHardwareGlove()
{
	// do later.
}

void Glove::startSendingData()
{
	mPort->open(QIODevice::ReadOnly);

	QObject::connect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Glove::stopSendingData()
{
	QObject::disconnect(mPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

	mPort->close();
}

bool Glove::isDataSending()
{
	return mPort->isOpen();
}

bool Glove::isPortSet()
{
	return !(mPort->portName().isEmpty());
}

QList<int> *Glove::data()
{
	return &mLastData;
}

void Glove::onReadyRead()
{
	if (!mPort->bytesAvailable()) {
		return;
	}

	mBytes = mPort->readAll();

	if (!hasHeader()) {
		return;
	}

	getDataFromFlexSensors();

	emit dataIsRead();
}

bool Glove::hasHeader() const
{
	union {
		char chars[4];
		uint32_t header;
	} head;

	for (int i = 0; i < 4; i++) {
		head.chars[i] = mBytes[i];
	}

	return ((int)head.header == GloveConsts::header);
}

void Glove::getDataFromFlexSensors()
{
	union {
		char chars[GloveConsts::numberOfSensors * 4];
		uint32_t vals[GloveConsts::numberOfSensors];
	} fingers;

	for (int i = 4; i < GloveConsts::numberOfSensors * 4 + 4; i++) {
		fingers.chars[i - 4] = mBytes[i];
	}

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mLastData[i] = (int)fingers.vals[i];
	}
}

void Glove::setPortSettings()
{
	mPort = new QSerialPort;

	mPort->setBaudRate(QSerialPort::Baud115200);
	mPort->setDataBits(QSerialPort::Data8);
	mPort->setParity(QSerialPort::NoParity);
	mPort->setStopBits(QSerialPort::OneStop);
	mPort->setFlowControl(QSerialPort::NoFlowControl);
}
