#ifndef GLOVECALIBRATOR_H
#define GLOVECALIBRATOR_H

#include <QObject>
#include <QList>

class FlexSensorCalibrator;

class GloveCalibrator : public QObject
{
	Q_OBJECT
public:
	GloveCalibrator();

	void startCalibrate();
	void stopCalibrate();
	void writeData(const QList<int> &data);

	QList<int> minCalibratedList();
	QList<int> maxCalibratedList();

signals:
	void calibrated();

protected:
	bool isCalibrated();

private:
	bool isCalibrateing;

	QList<FlexSensorCalibrator *> mFlexCalibrators;
};

#endif // GLOVECALIBRATOR_H
