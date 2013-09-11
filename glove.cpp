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
		lastData.prepend(0);
	}

	setPortSettings();
}

Glove::~Glove()
{
	if (port->isOpen()) {
		stopSendingData();
	}

	delete port;
}

void Glove::connectHardwareGlove()
{
	// do later.
}

void Glove::startSendingData()
{
	port->open(QIODevice::ReadOnly);

	QObject::connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void Glove::stopSendingData()
{
	QObject::disconnect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

	port->close();
}

bool Glove::isDataSending()
{
	return port->isOpen();
}

bool Glove::isPortSet()
{
	return port->portName().isEmpty();
}

QList<int> *Glove::data()
{
	return &lastData;
}

void Glove::onReadyRead()
{
	if (!port->bytesAvailable()) {
		return;
	}

	bytes = port->readAll();

	if (!hasHeader()) {
		return;
	}

	getDataFromFlexSensors();
}

bool Glove::hasHeader() const
{
	union {
		char chars[4];
		uint32_t header;
	} head;

	for (int i = 0; i < 4; i++) {
		head.chars[i] = bytes[i];
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
		fingers.chars[i - 4] = bytes[i];
	}

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		lastData[i] = (int)fingers.vals[i];
	}
}

void Glove::setPortSettings()
{
	port = new QSerialPort;

	port->setBaudRate(QSerialPort::Baud115200);
	port->setDataBits(QSerialPort::Data8);
	port->setParity(QSerialPort::NoParity);
	port->setStopBits(QSerialPort::OneStop);
	port->setFlowControl(QSerialPort::NoFlowControl);
}
