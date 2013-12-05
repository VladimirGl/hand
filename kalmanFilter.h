#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <QObject>

/**
 * @file kalmanFilter.h
 *
 * Implementation of KalmanFilter class.
 * This class filters the incoming values by the Kalman's method.
 */

class KalmanFilter
{
public:
	KalmanFilter(QList<int> state);

	/// Update and correct data.
	void correct(QList<int> data);

	/// Returns QList of filtered data.
	QList<int> getState();

private:
	QList<qreal> mPredicateState;
	QList<qreal> mPredicateCovaiance;

	QList<qreal> mPrevValueFactor;
	QList<qreal> mMeasurementNoise;
	QList<qreal> mMeasuredValueFactor;
	QList<qreal> mEnviromentNoise;

	QList<int> mState;
	QList<qreal> mCovariance;
};

#endif // KALMANFILTER_H
