#include "handInterface.h"

#include "hand.h"

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
	return mHand->isPortSet();
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

QList<int> *HandInterface::motorsDatas()
{
	return mHand->currentPosition();
}
