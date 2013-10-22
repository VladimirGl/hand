#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QQueue>

class FlexSensorCalibrator
{
public:
	FlexSensorCalibrator();
	void addValue(const int &value);

	int max() const { return mMax; }
	int min() const { return mMin; }

protected:
	void mean();
	void sum(const int &value);

	void maxPerformer();
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
