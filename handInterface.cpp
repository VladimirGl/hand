#include "handInterface.h"

#include "hand.h"

#include "consts.h"

#include <QDebug>

HandInterface::HandInterface() :
	mHand(new Hand)
{
}

HandInterface::~HandInterface()
{
	if (isHardwareHandSet()) {
		QObject::disconnect(mHand, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}

	delete mHand;
}

void HandInterface::setHardwareHand()
{
	mHand->connectHardwareHand();

	if (isHardwareHandSet()) {
		QObject::connect(mHand, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}
}

bool HandInterface::isHardwareHandSet()
{
//	return mHand->isPortSet();
	return true;
}

void HandInterface::startSendingDatas()
{
	mHand->startSendingData();
}

void HandInterface::stopSendingDatas()
{
	mHand->stopSendingData();

}
void HandInterface::moveMotor(const int &num, const int &value)
{
	mHand->moveMotor(num, value);
}

void HandInterface::moveMotors(const QList<int> &data)
{
	qDebug() << data;

	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		moveMotor(i, data.at(i));
	}

	qDebug() << "stop";
}

QList<int> *HandInterface::motorsDatas()
{
	return mHand->currentPosition();
}
