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
	User() :
		mDOFListSize(0),
		mConformityListSize(0)
	{}

	void addDOF(const int &min, const int &max);
	/// Adds new conformity of sensor and motor.
	void addSensorMotorConformity(const int &sensor, const int &motor);

	int DOFSize() const { return mDOFListSize; }
	int conformitySize() const { return mConformityListSize; }

	/**
	 * Returns QList of motors, that match sensor with sensurNumber number.
	 * Several motors can match one sensor, but not the other way.
	 */
	QList<int> motorList(int const& sensorNumber) const;

	int sensorMax(int const& num) const;
	int sensorMin(int const& num) const;

private:
	QList<DegreeOfFreedom> mFreedomList;
	QMultiMap<int, int> mSensorMotorConformityMap;

	int mDOFListSize;
	int mConformityListSize;
};

#endif // USER_H
