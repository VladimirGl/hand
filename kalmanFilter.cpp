#include "kalmanFilter.h"

KalmanFilter::KalmanFilter(qreal measuredNoise, qreal enviromentNoise,
                           qreal prevValueFactor, qreal measuredValueFactor)
{
    mMeasurementNoise = measuredNoise;
    mEnviromentNoise = enviromentNoise;
    mPrevValueFactor = prevValueFactor;
    mMeasuredValueFactor = measuredValueFactor;
}

void KalmanFilter::SetState(qreal state, qreal covariance)
{
    mState = state;
    mCovariance = covariance;
}

void KalmanFilter::Correct(qreal data)
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

qreal KalmanFilter::State()
{
    return mState;
}
