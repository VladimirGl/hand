#include "gloveCalibrator.h"

#include "flexSensorCalibrator.h"
#include "consts.h"

GloveCalibrator::GloveCalibrator() :
	isCalibrateing(false)
{}

void GloveCalibrator::startCalibrate()
{
	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		FlexSensorCalibrator *temp = new FlexSensorCalibrator;

		mFlexCalibrators.append(temp);
	}

	isCalibrateing = true;
}

void GloveCalibrator::stopCalibrate()
{
	isCalibrateing = false;

	while (!mFlexCalibrators.isEmpty()) {
		FlexSensorCalibrator *temp = mFlexCalibrators.takeFirst();

		delete temp;
		temp = NULL;
	}
}

void GloveCalibrator::writeData(const QList<int> &data)
{
	if (!isCalibrateing) {
		return;
	}

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		mFlexCalibrators.at(i)->addValue(data.at(i));
	}
}

QList<int> GloveCalibrator::minCalibratedList()
{
	QList<int> minList;

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		minList.append(mFlexCalibrators.at(i)->min());
	}

	return minList;
}

QList<int> GloveCalibrator::maxCalibratedList()
{
	QList<int> maxList;

	for (int i = 0; i < GloveConsts::numberOfSensors; i++) {
		maxList.append(mFlexCalibrators.at(i)->max());
	}

	return maxList;
}
