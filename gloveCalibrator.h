#ifndef GLOVECALIBRATOR_H
#define GLOVECALIBRATOR_H

#include <QObject>
#include <QList>

/**
* @file gloveCalibrator.h
*
* Implementation of the GloveCalibratorClass.
* Used to calibrate all sensors of the glove.
* Uses the FlexSensorCalibrator's to calibrate flex sensors.
*/

class FlexSensorCalibrator;

class GloveCalibrator : public QObject
{
	Q_OBJECT
public:
	GloveCalibrator();

	/// Creates an object of the FlexSensorCalibrator class for each flex sensor.
	void startCalibrate();
	/// Removes all created FlexSensorCalibrator objects.
	void stopCalibrate();
	/**
	* Writes sensor values from data to corresponding FlexSensorCalibrator objects.
	* Can be called only between startCalibrate() and stopCalibrate().
	*/
	void writeData(const QList<int> &data);

	/// Returns the list of min flex sensors values.
	QList<int> minCalibratedList();
	/// Returns the list of max flex sensors values.
	QList<int> maxCalibratedList();

signals:
	void calibrated();

private:
	bool isCalibrateing;

	QList<FlexSensorCalibrator *> mFlexCalibrators;
};

#endif // GLOVECALIBRATOR_H
