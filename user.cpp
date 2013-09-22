#include "user.h"

User::User(const QString &freedomFileName
		, const QString &conformityFileName)
{
	fillFreedomListFromFile(freedomFileName);
	fillSensorMotorConformityMapFromFile(conformityFileName);
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

void User::fillFreedomListFromFile(const QString &fileName)
{
	// do later
}

void User::fillSensorMotorConformityMapFromFile(const QString &fileName)
{
	// do later
}

