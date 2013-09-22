#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QList>

/**
* @file user.h
*
* Implementation of User class.
* Contains information about glove properties and sensor-motor conformity.
*/

#include "degreeOfFreedom.h"

class User
{
public:
	User()
	{}

	User(QString const& freedomFileName
			, QString const& conformityFileName);

	/**
	 * Returns QList of motors, that match sensor with sensurNumber number.
	 * Several motors can match one sensor, but not the other way.
	 */
	QList<int> motorList(int const& sensorNumber) const;

	int sensorMax(int const& num) const;
	int sensorMin(int const& num) const;

	void fillFreedomListFromFile(QString const& fileName);
	void fillSensorMotorConformityMapFromFile(QString const& fileName);

private:
	QList<DegreeOfFreedom> mFreedomList;
	QMultiMap<int, int> mSensorMotorConformityMap;
};

#endif // USER_H
