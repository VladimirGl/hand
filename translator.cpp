#include "translator.h"

#include "gloveInterface.h"
#include "handInterface.h"
#include "fileActionPerformer.h"
#include "user.h"
#include "gloveCalibrator.h"

#include "consts.h"

#include <QDebug>

Translator::Translator() :
	mConnectionType(noConnection),
	mUser(new User),
	mFileActionPerformer(new FileActionPerformer),
	mGloveCalibrator(new GloveCalibrator),
	mGloveInterface(new GloveInterface),
	mHandInterface(new HandInterface)
{
	for (int i = 0; i < HandConsts::numberOfMotors; i++) {
		mUser->addSensorMotorConformity(i, i);

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
		mGloveInterface->startSendingDatas();
		connect(mGloveInterface, SIGNAL(dataIsRead()), this, SLOT(convertData()));
		break;
	}
	case actionToHand: {
		mHandInterface->startSendingDatas();
		connect(mFileActionPerformer, SIGNAL(onReadyLoad()), this, SLOT(convertData()));
		break;
	}
	case calibrate: {
		mGloveInterface->startSendingDatas();
		mGloveCalibrator->startCalibrate();
		connect(mGloveInterface, SIGNAL(dataIsRead()), this, SLOT(sendDataToCalibrator()));
		connect(mGloveCalibrator, SIGNAL(calibrated()), this, SLOT(stopCalibrate()));
	}
	}
}

void Translator::stopConnection()
{
	switch (mConnectionType)
	{
	case noConnection: {
		return;
	}
	case gloveToHand: {
		mGloveInterface->stopSendingDatas();
		disconnect(mGloveInterface, SIGNAL(dataIsRead()), this, SLOT(convertData()));
		break;
	}
	case actionToHand: {
		mHandInterface->stopSendingDatas();
		disconnect(mFileActionPerformer, SIGNAL(onReadyLoad()), this, SLOT(convertData()));
		break;
	}
	case calibrate: {
		mGloveInterface->stopSendingDatas();
		disconnect(mGloveInterface, SIGNAL(dataIsRead()), this, SLOT(sendDataToCalibrator()));
		disconnect(mGloveCalibrator, SIGNAL(calibrated()), this, SLOT(stopCalibrate()));
		break;
	}
	}
}

void Translator::setConnectionType(const ConnectionType &type)
{
	stopConnection();

	mConnectionType = type;
}

void Translator::startLoadAction(const QString &fileName)
{
	if (mFileActionPerformer->isLoaded()) {
		stopLoadAction();
	}

	setConnectionType(actionToHand);
	mFileActionPerformer->startLoad(fileName);

	if ((mFileActionPerformer->isFileCorrect())) {
		startConnection();
	}
}

void Translator::stopLoadAction()
{
	if (!mFileActionPerformer->isLoaded()) {
		return;
	}

	setConnectionType(noConnection);

	mFileActionPerformer->stopLoad();

	emit loadingStoped();
}

void Translator::startSaveAction(const QString &fileName, const int &freq)
{
	if (mFileActionPerformer->isSaved()) {
		stopSaveAction();
	}

	setConnectionType(gloveToHand);
	startConnection();

	mFileActionPerformer->startSave(freq, GloveConsts::numberOfSensors, fileName);
}

void Translator::stopSaveAction()
{
	setConnectionType(noConnection);

	mFileActionPerformer->stopSave();
}

void Translator::startCalibrate()
{
	setConnectionType(calibrate);

	startConnection();
}

void Translator::stopCalibrate()
{
	qDebug() << "max" << mGloveCalibrator->maxCalibratedList();
	qDebug() << "min" << mGloveCalibrator->minCalibratedList();

	QList<int> maxList = mGloveCalibrator->maxCalibratedList();
	QList<int> minList = mGloveCalibrator->minCalibratedList();

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mUser->addDOF(minList.at(i), maxList.at(i));
	}

	mGloveCalibrator->stopCalibrate();

	stopConnection();
}

void Translator::convertData()
{
	if (mConnectionType == noConnection) {
		return;
	}

	if (mConnectionType == actionToHand) {
		QList<int> temp = mFileActionPerformer->data();

		if (!mFileActionPerformer->isFileCorrect() || mFileActionPerformer->isFileEnd()) {
			stopLoadAction();
			return;
		}

		saveConvertedData(temp);
		sendDataToHand();

		return;
	}

	saveSensorsData(mGloveInterface->gloveDatas());

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		QList<int> motorList = mUser->motorList(i);

		for (int j = 0; j < motorList.size(); j++) {
			mConvertedDatas[motorList.at(j)] = map(mSensorDatas[i], mUser->sensorMin(i), mUser->sensorMax(i));
		}
	}

	sendDataToHand();
}

void Translator::sendDataToCalibrator()
{
	mGloveCalibrator->writeData(mGloveInterface->gloveDatas());
}

void Translator::sendDataToHand()
{
	if (mFileActionPerformer->isSaved()) {
		mFileActionPerformer->writeData(mConvertedDatas);
	}

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
	int val = map(value, min, max, HandConsts::motorMinValue, HandConsts::motorMaxValue);

	if (val > HandConsts::motorMaxValue) {
		val = HandConsts::motorMaxValue;
	}

	if (val < HandConsts::motorMinValue) {
		val = HandConsts::motorMinValue;
	}

	return val;
}


