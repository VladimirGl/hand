#include "user.h"

#include "degreeOfFreedom.h"

User::User(const QString &freedomFileName
		, const QString &conformityFileName)
{
	fillFreedomListFromFile(freedomFileName);
	fillSensorMotorConformityMapFromFile(conformityFileName);
}

QList<int> User::motorList(int const& sensorNumber) const
{
	QList<int> values = sensorMotorConformityMap.values(sensorNumber);

	return values;
}

void User::fillFreedomListFromFile(const QString &fileName)
{
	// do later
}

void User::fillSensorMotorConformityMapFromFile(const QString &fileName)
{
	// do later
}

