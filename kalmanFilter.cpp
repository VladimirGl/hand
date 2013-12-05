#include "kalmanFilter.h"
#include "consts.h"

KalmanFilter::KalmanFilter(QList<int> state)
{
	mState = state;

	for (int i = 0; i < GloveConsts::numberOfSensors; i++)
	{
		mMeasurementNoise.prepend(KalmanConsts::measuredNoise);
		mEnviromentNoise.prepend(KalmanConsts::enviromentNoise);
		mPrevValueFactor.prepend(KalmanConsts::prevValueFactor);
		mMeasuredValueFactor.prepend(KalmanConsts::measuredValueFactor);
		mCovariance.prepend(KalmanConsts::covariance);
	}
}

void KalmanFilter::correct(QList<int> data)
{
	for (int i = 0; i < GloveConsts::numberOfSensors; i++)
	{
		//prediction
		mPredicateState.removeAt(i);
		mPredicateState.insert(i, mPrevValueFactor.at(i) * mState.at(i));
		mPredicateCovaiance.removeAt(i);
		mPredicateCovaiance.insert(i, mPrevValueFactor.at(i) * mCovariance.at(i) * mPrevValueFactor.at(i)
				+ mMeasurementNoise.at(i));

		//data correction
		qreal kalmanCoeff = mMeasuredValueFactor.at(i) * mPredicateCovaiance.at(i) /
				(mMeasuredValueFactor.at(i) * mPredicateCovaiance.at(i) * mMeasuredValueFactor.at(i)
				 + mEnviromentNoise.at(i));
		mState.removeAt(i);
		mState.insert(i, (int)(mPredicateState.at(i) + kalmanCoeff * (data.at(i)
						 - mMeasuredValueFactor.at(i) * mPredicateState.at(i))));
		mCovariance.removeAt(i);
		mCovariance.insert(i, (1 - kalmanCoeff * mMeasuredValueFactor.at(i)) * mPredicateCovaiance.at(i));
	}
}

QList<int> KalmanFilter::getState()
{
	return mState;
}
