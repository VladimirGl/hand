#include "kalmanFilter.h"

KalmanFilter::KalmanFilter(qreal measuredNoise, qreal enviromentNoise,
                           qreal prevValueFactor, qreal measuredValueFactor)
{
    mMeasurementNoise = measuredNoise;
    mEnviromentNoise = enviromentNoise;
    mPrevValueFactor = prevValueFactor;
    mMeasuredValueFactor = measuredValueFactor;
}

void KalmanFilter::setState(qreal state, qreal covariance)
{
    mState = state;
    mCovariance = covariance;
}

void KalmanFilter::correct(qreal data)
{
    //prediction
    mPredicateState = mPrevValueFactor * mState;
    mPredicateCovaiance = mPrevValueFactor * mCovariance * mPrevValueFactor + mMeasurementNoise;

    //data correction
    qreal kalmanCoeff = mMeasuredValueFactor * mPredicateCovaiance /
            (mMeasuredValueFactor * mPredicateCovaiance * mMeasuredValueFactor + mEnviromentNoise);
    mState = mPredicateState + kalmanCoeff * (data - mMeasuredValueFactor * mPredicateState);
    mCovariance = (1 - kalmanCoeff * mMeasuredValueFactor) * mPredicateCovaiance;
}

qreal KalmanFilter::state()
{
    return mState;
}
