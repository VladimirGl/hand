#include "flexSensorCalibrator.h"

#include "consts.h"

const int queueSize = 30;

FlexSensorCalibrator::FlexSensorCalibrator() :
	mSum(0),
	mMean(0),
	mMin(SensorsConsts::max),
	mMax(SensorsConsts::min),
	mIsQueueFilled(false)
{}

void FlexSensorCalibrator::addValue(const int &value)
{
	if (!mIsQueueFilled) {
		mData.enqueue(value);

		if (mData.size() == queueSize) {
			mIsQueueFilled = true;

			for (int i = 0; i < queueSize; i++) {
				mSum += mData.at(i);
			}
		}

		return;
	}

	sum(value);
	mean();

	maxPerformer();
	minPerformer();

	mData.enqueue(value);
	mData.dequeue();
}

void FlexSensorCalibrator::mean()
{
	mMean = (int)(mSum / queueSize);
}

void FlexSensorCalibrator::sum(const int &value)
{
	mSum -= mData.head();
	mSum += value;
}

void FlexSensorCalibrator::maxPerformer()
{
	if (mMax < mMean) {
		mMax = mMean;
	}
}

void FlexSensorCalibrator::minPerformer()
{
	if (mMin > mMean) {
		mMin = mMean;
	}
}
