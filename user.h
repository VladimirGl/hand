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

class DegreeOfFreedom;

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

	void fillFreedomListFromFile(QString const& fileName);
	void fillSensorMotorConformityMapFromFile(QString const& fileName);

private:
	QList<DegreeOfFreedom> freedomList;
	QMultiMap<int, int> sensorMotorConformityMap;
};

#endif // USER_H
