#include "user.h"

void User::addDOF(const int &min, const int &max)
{
	DegreeOfFreedom temp(min, max);

	mFreedomList.append(temp);

	mDOFListSize++;
}

void User::addSensorMotorConformity(const int &sensor, const int &motor)
{
	mSensorMotorConformityMap.insert(sensor, motor);

	mConformityListSize++;
}


QList<int> User::motorList(int const& sensorNumber) const
{
	QList<int> values = mSensorMotorConformityMap.values(sensorNumber);

	return values;
}

int User::sensorMax(int const& num) const
{
	return mFreedomList.at(num).max();
}

int User::sensorMin(int const& num) const
{
	return mFreedomList.at(num).min();
}

