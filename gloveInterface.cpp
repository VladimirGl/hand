#include "gloveInterface.h"

#include "glove.h"

GloveInterface::GloveInterface() :
	mGlove(new Glove),
	mIsConnected(false)
{
}

GloveInterface::~GloveInterface()
{
	if (isHardwareGloveSet()) {
		QObject::disconnect(mGlove, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}

	delete mGlove;
}

void GloveInterface::setHardwareGlove(const QString &portName)
{
	mGlove->connectHardwareGlove(portName);
}

bool GloveInterface::isHardwareGloveSet()
{
	return mGlove->isPortSet();
}

bool GloveInterface::isDataSending() const
{
	return mGlove->isDataSending();
}

void GloveInterface::startSendingDatas()
{
	if (isHardwareGloveSet()) {
		QObject::connect(mGlove, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}

	mGlove->startSendingData();
}

void GloveInterface::stopSendingDatas()
{
	if (isHardwareGloveSet()) {
		QObject::connect(mGlove, SIGNAL(dataIsRead()), this, SIGNAL(dataIsRead()));
	}

	mGlove->stopSendingData();
}

QList<int> GloveInterface::gloveDatas()
{
	return mGlove->data();
}
