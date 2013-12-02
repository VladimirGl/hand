#include "gloveCalibrator.h"

#include "flexSensorCalibrator.h"
#include "consts.h"

#include <QDebug>

GloveCalibrator::GloveCalibrator() :
	isCalibrateing(false)
{}

void GloveCalibrator::startCalibrate()
{
	if (isCalibrateing) {
		stopCalibrate();
	}

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

	for (int i = 0; i < mFlexCalibrators.size(); i++) {
		mFlexCalibrators.at(i)->addValue(data.at(i));
	}
}

QList<int> GloveCalibrator::minCalibratedList()
{
	if (!isCalibrateing) {
		return QList<int>();
	}

	QList<int> minList;

	for (int i = 0; i < mFlexCalibrators.size(); i++) {
		minList.append(mFlexCalibrators.at(i)->min());
	}

	return minList;
}

QList<int> GloveCalibrator::maxCalibratedList()
{
	if (!isCalibrateing) {
		return QList<int>();
	}

	QList<int> maxList;

	for (int i = 0; i < mFlexCalibrators.size(); i++) {
		maxList.append(mFlexCalibrators.at(i)->max());
	}

	return maxList;
}
