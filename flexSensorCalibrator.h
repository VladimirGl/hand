#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QQueue>

/**
* @file flexSensorCalibrator.h
*
* Implementation of the class FlexSensorCalibrator.
* Used to calibrate one flex sensor.
*/

class FlexSensorCalibrator
{
public:
	FlexSensorCalibrator();

	/// Adds one value to the data queue. Then calls sum(value), mean and min/max performers.
	void addValue(const int &value);

	int max() const { return mMax; }
	int min() const { return mMin; }

protected:
	/// Considers the mean of queue elements
	void mean();
	/// Considers the sum of queue elements.
	void sum(const int &value);

	/// Changed max value, if mean() > old max value.
	void maxPerformer();
	/// Changed min value, if mean() < old min value.
	void minPerformer();

private:
	QQueue<int> mData;

	int mSum;
	int mMean;

	int mMax;
	int mMin;

	bool mIsQueueFilled;
};

#endif // CALIBRATOR_H
