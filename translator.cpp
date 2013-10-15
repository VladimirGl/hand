#include "translator.h"

#include "gloveInterface.h"
#include "handInterface.h"
#include "fileActionPerformer.h"
#include "user.h"

#include "consts.h"

Translator::Translator() :
	mConnectionType(noConnection),
	mUser(new User),
	mFileActionPerformer(new FileActionPerformer),
	mGloveInterface(new GloveInterface),
	mHandInterface(new HandInterface)
{
	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mConvertedDatas.prepend(0);
	}

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mSensorDatas.prepend(0);
	}
}

Translator::~Translator()
{
	delete mGloveInterface;
	delete mHandInterface;
}

bool Translator::connectGlove()
{
	mGloveInterface->setHardwareGlove();

	return mGloveInterface->isHardwareGloveSet();
}

bool Translator::connectHand()
{
	mHandInterface->setHardwareHand();

	return mHandInterface->isHardwareHandSet();
}

void Translator::startConnection()
{
	switch (mConnectionType)
	{
	case noConnection: {
		return;
	}
	case gloveToHand: {
		connect(mGloveInterface, SIGNAL(dataIsRead()), this, SLOT(convertData()));
		break;
	}
	case actionToHand: {
		connect(mFileActionPerformer, SIGNAL(commandIsSend()), this, SLOT(convertData()));
		break;
	}
	}
}

void Translator::convertData()
{
	if (mConnectionType == noConnection) {
		return;
	}

	if (mConnectionType == actionToHand) {
		saveConvertedData(mFileActionPerformer->data());
		sendDataToHand();

		return;
	}

	saveSensorsData(*mGloveInterface->gloveDatas());

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		QList<int> motorList = mUser->motorList(i);

		for (int j = 0; j < motorList.size(); j++) {
			mConvertedDatas[motorList.at(j)] = map(mSensorDatas[i], mUser->sensorMin(i), mUser->sensorMax(i));
		}
	}

	sendDataToHand();
}

void Translator::sendDataToHand()
{
	mHandInterface->moveMotors(mConvertedDatas);
}

void Translator::saveConvertedData(QList<int> const& data)
{
	for (int i = 0; i < HandConsts::numberOfMotors; i++)
	{
		mConvertedDatas[i] = data.at(i);
	}
}

void Translator::saveSensorsData(QList<int> const& data)
{
	for (int i = 0; i < GloveConsts::numberOfSensors; i++)
	{
		mSensorDatas[i] = data.at(i);
	}
}

int Translator::map(int const& value
		, int const& firstMin, int const& firstMax
		, int const& secondMin, int const& secondMax)
{
	return (((value - firstMin)
			* (secondMax - secondMin)
			/ (firstMax - firstMin))
			+ secondMin);
}

int Translator::map(int const& value
			, int const& min, int const& max)
{
	return map(value, min, max, HandConsts::motorMinValue, HandConsts::motorMaxValue);
}


